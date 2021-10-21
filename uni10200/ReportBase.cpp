#include "StdAfx.h"
#include <sstream>
#include "ReportBase.h"


ReportBase::ReportBase(void)
{
  m_lst_item.clear();
}

ReportBase::~ReportBase(void)
{
  m_lst_item.clear();
}

int ReportBase::getRowLen()
{
  int rs = 0;
  for (list<ReportItem>::iterator it = m_lst_item.begin(); it != m_lst_item.end(); ++it) {
    rs += it->m_len;
  }

  return rs;
}

void ReportBase::add_item_to_str(string& out_str, string& param, size_t len)
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


void ReportBase::add_item_to_str(string& out_str, int param, size_t len)
{
  stringstream ss;
  ss << param;

  add_item_to_str(out_str, ss.str(), len);
}

void ReportBase::create()
{
  m_lst_item.push_back(ReportItem(string("Esempio"), 10));
  m_lst_item.push_back(ReportItem(string("Prova"), 10));
  m_lst_item.push_back(ReportItem(string("Test"), 10));
}

void ReportBase::getHline(string& out_str)
{
  for (list<ReportItem>::iterator it = m_lst_item.begin(); it != m_lst_item.end(); ++it) {
    int len = it->m_len;
    while (len--) {
      out_str.push_back('-');
    }
    out_str += "-+-";
  }
  out_str += "\r\n";
}

void ReportBase::getDescRow(string& out_str)
{
  getHline(out_str);

  for (list<ReportItem>::iterator it = m_lst_item.begin(); it != m_lst_item.end(); ++it) {
    add_item_to_str(out_str, it->m_nome, it->m_len);
  }
  out_str += "\r\n";

  getHline(out_str);
}
