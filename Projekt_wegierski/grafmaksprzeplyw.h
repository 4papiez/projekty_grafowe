#ifndef GRAFMAKSPRZEPLYW_H
#define GRAFMAKSPRZEPLYW_H
#include<list>
#include<vector>
#include<iostream>
#include<deque>
#include<algorithm>

class GrafMaksPrzeplyw
{
public:
  GrafMaksPrzeplyw();
  int znajdzMaksPrzeplyw(std::vector<std::vector<int> > macierzWag);
  std::vector<std::vector<int> > getMacierzPrzeplywu();
private:
  std::vector<std::vector<int> > macierzPrzeplywu;
  int znajdzMinWage(std::list<int> trasa,std::vector<std::vector<int> >&macierzWag);
  void odejWageOdTrasy(std::list<int> trasa,std::vector<std::vector<int> >&macierzWag,const int waga);
  void generujMacierzPrzeplywu(std::vector<std::vector<int> > macierzWag, std::vector<std::vector<int> > macierzWagResult);
  void odwrocTrase(std::list<int> trasa, std::vector<std::vector<int> >&macierzWag, const int waga);
  std::list<int> generujTrasePrzeplyw(std::vector<std::vector<int> > macierzWag);
};

#endif // GRAFMAKSPRZEPLYW_H
