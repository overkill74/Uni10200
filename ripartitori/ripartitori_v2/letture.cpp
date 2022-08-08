#include "letture.h"

#include <overkill/ovk_csv.h>
#include <overkill/ovk_syslog.h>
#include <overkill/ovk_terminal.h>

#include <iostream>
#include <sstream>
#include <fstream>


//-----------------------------------------------
Letture::Utente::Utente(const list<string>& lst)
{
    auto it = lst.begin();
    if (it == lst.end()) { return; }
    nome_letture = *it++;
    if (it == lst.end()) { return; }
    ovk_lexical_cast(*it++, unita);
    if (it == lst.end()) { return; }
    ovk_lexical_cast(*it++, particella);
    if (it == lst.end()) { return; }
    ovk_lexical_cast(*it++, sub);
    if (it == lst.end()) { return; }
    ovk_lexical_cast(*it++, millesimi);
    while (it != lst.end()) {
        cod_rip.push_back(*it++);
    }
}

//-----------------------------------------------
Letture::Letture()
{

}

//-----------------------------------------------
bool Letture::loadFromCsv(const string& path)
{
    OvkCsv csv(".",
               {"INDIRIZZO", "PIANO", "NOME UTENTE", "NR DISPOSITIVO", "VALORE LETTURA"});
    if (!csv.loadFromFile(path, true)) {
        OVK_LOG_ERR("Non posso leggere le letture in: %s", path.c_str());
        string path_ex("./letture_v2_empty.csv");
        OVK_LOG_WARNING("Creo un template vuoto in: %s", path_ex.c_str());
        csv.writeToFile(path_ex);
        return false;
    }

    int i=0;
    for (list<list<string>>::iterator it=csv.getBegin(); it!=csv.getEnd(); ++it, ++i) {
        if (it->size() < 5) {
            OVK_LOG_ALERT("Linea %d malformata", i);
            continue;
        }
        // Load into vector
        // 0 - "INDIRIZZO"
        // 1 - "PIANO"
        // 2 - "NOME UTENTE"
        // 3 - "NR DISPOSITIVO"
        // 4 - "VALORE LETTURA"

        vector<string> campi;
        for (auto& x: *it) {
            campi.push_back(x);
        }

        if (campi.size() < 5) {
            OVK_LOG_CRIT("Linea Malformata");
            return false;
        }

        map<string, vector<Ripartitore>>::iterator item = m_db_letture.find(campi.at(2));
        Ripartitore rpt = Ripartitore(campi.at(3),
                                      stod(campi.at(4)),
                                      campi.at(0),
                                      campi.at(1)
                                      );
        if (item == m_db_letture.end()) {
            // New Item
            m_db_letture.insert(pair<string, vector<Ripartitore>>(campi.at(2), {rpt}));
        }
        else {
            item->second.push_back(rpt);
        }
    }

    return true;
}

//-----------------------------------------------
bool Letture::loadTemplate(const string& path)
{
    OvkCsv tmplt(".",
                 {"Nominativo","Unità","Part","Sub","Millesimi",
                  "Ripart 1","Ripart 2","Ripart 3","Ripart 4","Ripart 5","Ripart 6","Ripart 7","Ripart 8","Ripart 9","Ripart 10"});
    if (!tmplt.loadFromFile(path, true)) {
        OVK_LOG_ERR("Non posso leggere il template in: %s", path.c_str());
        string path_ex("./template_v2_empty.csv");
        OVK_LOG_WARNING("Creo un template vuoto in: %s", path_ex.c_str());
        tmplt.writeToFile(path_ex);
        return false;
    }

    int i=0;
    for (list<list<string>>::iterator it=tmplt.getBegin(); it!=tmplt.getEnd(); ++it, ++i) {
        if (it->size() < 4) {
            OVK_LOG_ALERT("Linea %d malformata", i);
            continue;
        }
        Utente usr(*it);
        m_db_template.insert(pair<string, Utente>(*it->begin(), usr));
    }

    return true;
}

//-----------------------------------------------
void Letture::calcolaScatti()
{
    for (auto& it: m_db_letture)
    {
        // calcola consumo totale
        double consumo = 0;
        bool found=false;

        for (auto& r: it.second) {
            consumo += r.consumo;
        }

        // Cerca nel template
        for (auto& tt: m_db_template)
        {
            if (found) { break; }
            Utente& usr = tt.second;
            for (auto& r: it.second)
            {
                if (found) { break; }
                for (auto& cr: usr.cod_rip)
                {
                    if (!cr.compare(r.cod_rip)) {
                        // TROVATO!
                        found = true;
                        usr.nome_letture = it.first;
                        usr.tot_scatti = consumo;
                        usr.indirizzo = r.indirizzo;
                        usr.piano = r.piano;
                        break;
                    }
                }
            }
        }

        // Segnala errore
        if (!found) {
            OVK_LOG_CRIT("Errore: %s (%s)", it.first.c_str());
            //cout << "*****************" << it.first << endl;
        }
    }
}

//-----------------------------------------------
void Letture::printByName()
{
    for (auto& it: m_db_letture) {
        cout << it.first;
        for (auto& r: it.second) {
            cout << "[" << r.cod_rip << "]=" << r.consumo << ", ";
        }
        cout << endl;
    }
}

//-----------------------------------------------
void Letture::printTemplate()
{
    double tot_mil=0;
    double tot_scatti=0;
    for (auto& it: m_db_template) {
        Utente& usr = it.second;
        cout << it.first << ",";
        cout << usr.indirizzo << ",";
        cout << usr.piano << ",";
        cout << usr.unita << ",";
        cout << usr.particella << ",";
        cout << usr.sub << ",";
        cout << usr.millesimi << ",";
        cout << usr.nome_letture << ",";
        char tmp[64];
        sprintf(tmp, "%.3f", usr.tot_scatti / 1000);
        cout << tmp << ",";
        for (auto& cr : usr.cod_rip) {
            cout << cr << ",";
        }
        cout << endl;
        tot_mil = tot_mil + usr.millesimi;
        tot_scatti = tot_scatti + usr.tot_scatti;
    }
    cout << "Totale Millesimi: " << tot_mil << endl;
    cout << "Totale Scatti: " << tot_scatti << endl;
}

//-----------------------------------------------
bool Letture::saveCsvByName(const string& path)
{
    OvkCsv csv(".",
               {"Nominativo","Indirizzo","Piano","Unità","Part","Sub","Millesimi",
                "Nominativo Letture","Totale Scatti",
                "Ripart 1","Ripart 2","Ripart 3","Ripart 4","Ripart 5",
                "Ripart 6","Ripart 7","Ripart 8","Ripart 9","Ripart 10"}
               );
    for (auto& it: m_db_template) {
        Utente& usr = it.second;
        list<string> row;
        row.push_back(it.first);
        row.push_back(usr.indirizzo);
        row.push_back(usr.piano);
        row.push_back(::to_string(usr.unita));
        row.push_back(::to_string(usr.particella));
        row.push_back(::to_string(usr.sub));
        row.push_back(::to_string(usr.millesimi));
        row.push_back(usr.nome_letture);
        row.push_back(::to_string(usr.tot_scatti));

        for (auto& cr : usr.cod_rip) {
            row.push_back(cr);
        }

        csv.appendRow(row);
    }

    csv.writeToFile(path);


    //    list<string> prow;
    //    csv.toPrintableString(prow);
    //    for (auto& it:prow) {
    //        cout << it << endl;
    //    }

    return true;
}

//-----------------------------------------------
bool Letture::saveCsvRipartitore(const string& path)
{
    OvkCsv csv(".",
               {"Utente","Dispositivo","Lettura"}
               );
    for (auto& it: m_db_letture) {
        string name(it.first);

        for (auto& r: it.second) {
            csv.appendRow({name, r.cod_rip, ::to_string(r.consumo)});
        }
    }

    return csv.writeToFile(path);
}

