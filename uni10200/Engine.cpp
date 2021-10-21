#include "StdAfx.h"
#include "Condominio.h"
#include "utente.h"
#include "radiatore.h"
#include "Engine.h"

Engine::Engine(void)
  : m_condominio(0)
{
}

Engine::~Engine(void)
{
  if (m_condominio) delete m_condominio;
}

Utente* Engine::search_user(string& nome)
{
  for (list<Utente*>::iterator it = m_condominio->m_lst_usr.begin(); it != m_condominio->m_lst_usr.end(); ++it) {
    if ((*it)->m_nome == nome) {
      return *it;
    }
  }

  return 0;
}


bool Engine::createCondominio(string& nome, string& indirizzo, string& citta)
{
  if (m_condominio) delete m_condominio;
  m_condominio = new Condominio();

  if (!m_condominio) return false;

  m_condominio->m_nome = nome;
  m_condominio->m_citta = citta;
  m_condominio->m_indirizzo = indirizzo;

  return true;
}

bool Engine::addUser(string& nome, string& scala, int piano)
{
  Utente* pu = search_user(nome);

  if (pu) return false;

  pu = new Utente(nome);
  pu->m_lst_radiatori.clear();
  pu->m_scala = scala;
  pu->m_piano = piano;

  m_condominio->addUser(pu);

  return true;
}

Radiatore* Engine::allocRadiatore()
{
  return new Radiatore();
}
  
bool Engine::addRadiatore(string& ursname, Radiatore* rad)
{
  Utente* pu = search_user(ursname);

  if (!pu) return false;

  pu->addRadiatore(rad);

  return true;
}

bool Engine::getReportUser(string& ursname, string& out_str)
{
  Utente* pu = search_user(ursname);

  if (!pu) return false;

  return pu->getReportRadiatori(out_str);
}
