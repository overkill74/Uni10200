#include "StdAfx.h"
#include "radiatore.h"
#include "utente.h"


Utente::Utente(string& nome)
  : m_nome(nome)
  , m_scala("")
  , m_piano(0)
{
  m_lst_radiatori.clear();
}


Utente::~Utente(void)
{
  for (list<Radiatore*>::iterator it = m_lst_radiatori.begin(); it != m_lst_radiatori.end(); ++it) {
    if (*it) delete *it;
  }
  m_lst_radiatori.clear();
}

void Utente::addRadiatore(Radiatore* rad)
{
  m_lst_radiatori.push_back(rad);
}

bool Utente::getReportRadiatori(string& out_str)
{
  out_str.clear();

  for (list<Radiatore*>::iterator it = m_lst_radiatori.begin(); it != m_lst_radiatori.end(); ++it) {
    if (*it) {
      if (it == m_lst_radiatori.begin()) {
        (*it)->getReportStringHead(out_str);
      }
      (*it)->getReportString(out_str);
    }
  }

  return true;
}
