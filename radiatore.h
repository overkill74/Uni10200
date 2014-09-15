
#pragma once

#include "ReportBase.h"
#include <string>
#include <list>

using namespace std;

class Conteggi
{
public:
  Conteggi()
    : m_anno(0)
    , m_valore(0)
  {}

  int m_anno;
  int m_valore;
};

class Radiatore
{
public:
  Radiatore(void);
  virtual ~Radiatore(void);

  void getReportStringHead(string& rpt);
  void getReportString(string& rpt);
  void getConteggi(int anno);

private:
  static void add_param(string& out_str, string& param, size_t len);
  static void add_param(string& out_str, int param, size_t len);

public:
  string         m_descrizione;
  int            m_lungh;
  int            m_alt;
  int            m_prof;
  int            m_interasse;
  int            m_potenza;
  string         m_code_rip;
  string         m_locale;
  list<Conteggi> m_conteggi;

private:
  ReportBase*    m_report;
};

