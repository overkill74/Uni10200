#ifndef LETTURE_H
#define LETTURE_H

#include <stdint.h>
#include <string>
#include <vector>
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
        Ripartitore(const string& cod, double cons) : cod_rip(cod), consumo(cons) {}
    public:
        string      cod_rip;    // Codice Ripartitore
        double      consumo;    // Consumo
    };

    class Utente
    {
    public:
        string          nome_letture;   // Nome sulla tabella delle letture
        string          unita;          // Unita' abitativa
        vector<string>  cod_rip;        // Codice ripartitore
        double          tot_scatti=0;   // Totale Scatti
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

protected:
    map<string, vector<Ripartitore>>    m_db_letture;   // Letture
    map<string, Utente>                 m_db_template;  // Utenti come da template
};

#endif // LETTURE_H
