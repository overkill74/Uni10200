#pragma once

#include <string>

using namespace std;

class Condominio;
class Utente;
class Radiatore;

class Engine
{
public:
  Engine(void);
  ~Engine(void);

  bool createCondominio(string& nome, string& indirizzo, string& citta);
  bool addUser(string& nome, string& scala, int piano);
  Radiatore* allocRadiatore();
  bool addRadiatore(string& ursname, Radiatore* rad);

  bool getReportUser(string& ursname, string& out_str);

private:
  Utente* search_user(string& nome);

private:
  Condominio* m_condominio;
};

