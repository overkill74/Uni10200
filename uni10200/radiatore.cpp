#include "StdAfx.h"
#include <sstream>
#include "radiatore.h"

//------------------------------------------------------------------------------
class ReportRadiatore : public ReportBase
{
public:
  ReportRadiatore()
    : ReportBase()
  {
    create();
  }
  ~ReportRadiatore() {}

  void create()
  {
    m_lst_item.push_back(ReportItem(string("Locale"), 16));
    m_lst_item.push_back(ReportItem(string("Descrizione"), 40));
    m_lst_item.push_back(ReportItem(string("L"), 5));
    m_lst_item.push_back(ReportItem(string("H"), 5));
    m_lst_item.push_back(ReportItem(string("INT"), 7));
    m_lst_item.push_back(ReportItem(string("Potenza"), 9));
    m_lst_item.push_back(ReportItem(string("Cod. Ripart."), 16));
  }
};

//------------------------------------------------------------------------------
Radiatore::Radiatore(void)
  : m_descrizione("Radiatore")
  , m_lungh(0)
  , m_alt(0)
  , m_prof(0)
  , m_interasse(0)
  , m_potenza(0)
  , m_code_rip("N.P.")
  , m_locale("N.D.")
{
  m_report = new ReportRadiatore();
}

Radiatore::~Radiatore(void)
{
  if (m_report) delete m_report;
}

void Radiatore::add_param(string& out_str, string& param, size_t len)
{
  if (param.length() <= len) {
    out_str.append(param);
    int spc = len - param.length();
    while (spc--) out_str.append(" ");
  }
  else {
    string::iterator it = param.begin();
    for (size_t x=0; x<len; ++x, ++it) {
      out_str.push_back(*it);
    }
  }

  out_str.append(" | ");
}

void Radiatore::add_param(string& out_str, int param, size_t len)
{
  stringstream ss;
  ss << param;

  add_param(out_str, ss.str(), len);
}

void Radiatore::getReportStringHead(string& rpt)
{
  m_report->getDescRow(rpt);
}

void Radiatore::getReportString(string& rpt)
{
  add_param(rpt, m_locale, 16);
  add_param(rpt, m_descrizione, 40);
  add_param(rpt, m_lungh, 5);
  add_param(rpt, m_alt, 5);
  add_param(rpt, m_interasse, 7);
  add_param(rpt, m_potenza, 9);
  add_param(rpt, m_code_rip, 16);

  rpt += "\r\n";
}

void Radiatore::getConteggi(int anno)
{
}

