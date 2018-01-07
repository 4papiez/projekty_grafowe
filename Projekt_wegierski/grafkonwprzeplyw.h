#ifndef GRAFKONWPRZEPLYW_H
#define GRAFKONWPRZEPLYW_H
#include<vector>
#include<cstdlib>
#include<iostream>

class GrafKonwPrzeplyw
{
public:
  GrafKonwPrzeplyw(const int val);
  /**
   * @brief konwersjaWagi Losuje wagi z przedzału 1 do MAX_VALUE
   * @param macierzSas
   */
  void konwersjaWagi(const std::vector<std::vector<bool> > macierzSas, const int val);
  
  /**
   * @brief konwersjaWagiSkojarzenia Zamienia po prostu bool na int
   * @param macierzSas
   */
  void konwersjaWagiSkojarzenia(const std::vector<std::vector<bool> > macierzSas, const int val);
  void konwersjaWagiSkojarzenia2(const std::vector<std::vector<bool> > macierzSas, const int val);
  std::vector<std::vector<int> >& getMacierzWag(){return macierzWag;}
  void setMacierzWag(std::vector<std::vector<int> > mac){this->macierzWag = mac;}
private:
  int MAX_VALUE;
  std::vector<std::vector<int> > macierzWag;
  
};

#endif // GRAFKONWPRZEPLYW_H
