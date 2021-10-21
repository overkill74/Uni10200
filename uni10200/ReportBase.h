#pragma once

#include <string>
#include <list>

using namespace std;

class ReportItem
{
public:
  ReportItem(string& nome, int len) : m_nome(nome), m_len(len) {};
  ~ReportItem(void) {};

  string m_nome;
  int    m_len;
};


class ReportBase
{
public:
  ReportBase(void);
  virtual ~ReportBase(void);

  int getRowLen();
  void getHline(string& out_str);
  void getDescRow(string& out_str);

  virtual void create();

private:
  void add_item_to_str(string& out_str, string& param, size_t len);
  void add_item_to_str(string& out_str, int param, size_t len);

protected:
  list<ReportItem> m_lst_item;
};

