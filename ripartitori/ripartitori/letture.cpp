#include "letture.h"

#include <iostream>
#include <sstream>
#include <fstream>

//-----------------------------------------------
Letture::Letture()
{

}

//-----------------------------------------------
bool Letture::loadFromCsv(const string& path)
{
    ifstream csv(path);
    if (!csv.is_open()) {
        return false;
    }

    string line;
    while (getline(csv, line))
    {
        vector<string> campi;
        string tmp;
        // Tokenize
        for (auto& i : line) {
            if (i == ',') {
                campi.push_back(tmp);
                tmp.clear();
                continue;
            }
            tmp.push_back(i);
        }
        if (!tmp.empty()) {
            campi.push_back(tmp);
        }
        // Add to map
        if (campi.size() < 3) {
            cout << "Malformed row: " << line << endl;
            continue;
        }

        map<string, vector<Ripartitore>>::iterator item = m_db_letture.find(campi.at(0));
        Ripartitore rpt = Ripartitore(campi.at(1), stod(campi.at(2)));
        if (item == m_db_letture.end()) {
            // New Item
            m_db_letture.insert(pair<string, vector<Ripartitore>>(campi.at(0), {rpt}));
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
    ifstream csv(path);
    if (!csv.is_open()) {
        return false;
    }

    string line;
    while (getline(csv, line))
    {
        vector<string> campi;
        string tmp;
        // Tokenize
        for (auto& i : line) {
            if (i == ',') {
                if (!tmp.empty()) {
                    campi.push_back(tmp);
                }
                tmp.clear();
                continue;
            }
            tmp.push_back(i);
        }
        if (!tmp.empty()) {
            campi.push_back(tmp);
        }


        // Add to map
        if (campi.size() < 3) {
            cout << "Malformed row: " << line << endl;
            continue;
        }

        Utente usr;
        usr.unita = campi.at(1);
        for (size_t x=2; x<campi.size(); ++x) {
            usr.cod_rip.push_back(campi.at(x));
        }

        m_db_template.insert(pair<string, Utente>(campi.at(0), usr));
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
                        break;
                    }
                }
            }
        }

        // Segnala errore
        if (!found) {
            cout << "*****************" << it.first << endl;
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
    for (auto& it: m_db_template) {
        Utente& usr = it.second;
        cout << it.first << ",";
        cout << usr.unita << ",";
        cout << usr.nome_letture << ",";
        char tmp[64];
        sprintf(tmp, "%.3f", usr.tot_scatti / 1000);
        cout << tmp << ",";
        for (auto& cr : usr.cod_rip) {
            cout << cr << ",";
        }
        cout << endl;
    }
}
