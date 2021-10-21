#pragma once

#include <list>
#include <string>

class Radiatore;

using namespace std;


class CoordCat
{
public:
  CoordCat()
    : m_mapp(0)
    , m_part(0)
    , m_sub(0)
  {};

  int m_mapp;
  int m_part;
  int m_sub;
};


class Utente
{
public:
  Utente(string& nome);
  ~Utente(void);

  void addRadiatore(Radiatore* rad);
  bool getReportRadiatori(string& out_str);

public:
  string           m_nome;
  string           m_scala;
  int              m_piano;
  CoordCat         m_cc;
  list<Radiatore*> m_lst_radiatori;
};

