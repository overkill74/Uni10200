#pragma once

#include <list>
#include <string>

class Utente;

using namespace std;

class Condominio
{
public:
  Condominio(void);
  ~Condominio(void);

  bool addUser(Utente* new_usr);

public:
  string        m_nome;
  string        m_indirizzo;
  string        m_citta;
  list<Utente*> m_lst_usr;
};

