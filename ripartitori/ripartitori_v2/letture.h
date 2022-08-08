#ifndef LETTURE_H
#define LETTURE_H

#include <stdint.h>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

///
/// \brief The Letture class
///
class Letture
{
public:
    class Ripartitore
    {
    public:
        Ripartitore(const string& cod, double cons,
                    const string& ind, const string& pian)
            : cod_rip(cod)
            , consumo(cons)
            , indirizzo(ind)
            , piano(pian)
        {}
    public:
        string      cod_rip;    // Codice Ripartitore
        double      consumo;    // Consumo
        string      indirizzo;  // Indirizzo
        string      piano;      // Piano
    };

    class Utente
    {
    public:
        Utente(const list<string>& lst);
    public:
        string          nome_letture;   // Nome sulla tabella delle letture
        uint32_t        unita;          // Unita' abitativa
        uint32_t        particella;     // Particella
        uint32_t        sub;            // Subalterno
        double          millesimi;      // Millesimi
        vector<string>  cod_rip;        // Codice ripartitore
        double          tot_scatti=0;   // Totale Scatti
        string          indirizzo;      // Indirizzo
        string          piano;          // Piano
    };

public:
    Letture();
    ///
    /// \brief loadFromCsv
    /// \param path
    /// \return success
    ///
    bool loadFromCsv(const string& path);
    ///
    /// \brief loadTemplate
    /// \param path
    /// \return success
    ///
    bool loadTemplate(const string& path);
    ///
    /// \brief printByName
    ///
    void printByName();
    ///
    /// \brief printTemplate
    ///
    void printTemplate();
    ///
    /// \brief calcolaScatti
    ///
    void calcolaScatti();
    ///
    /// \brief saveCsvByName
    /// \param path
    /// \return
    ///
    bool saveCsvByName(const string& path);
    ///
    /// \brief saveCsvRipartitore
    /// \param path
    /// \return
    ///
    bool saveCsvRipartitore(const string& path);

protected:
    map<string, vector<Ripartitore>>    m_db_letture;   // Letture
    map<string, Utente>                 m_db_template;  // Utenti come da template
};

#endif // LETTURE_H
