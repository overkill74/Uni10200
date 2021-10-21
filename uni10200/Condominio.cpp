#include "StdAfx.h"
#include "utente.h"
#include "Condominio.h"


Condominio::Condominio(void)
  : m_nome("Condominio")
  , m_indirizzo("Indirizzo")
  , m_citta("Città")
{
  m_lst_usr.clear();
}


Condominio::~Condominio(void)
{
  for (list<Utente*>::iterator it = m_lst_usr.begin(); it != m_lst_usr.end(); ++it) {
    if (*it) delete *it;
  }
  m_lst_usr.clear();
}


bool Condominio::addUser(Utente* new_usr)
{
  m_lst_usr.push_back(new_usr);

  return true;
}
