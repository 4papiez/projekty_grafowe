#ifndef GRAFGENERPRZEPLYW_H
#define GRAFGENERPRZEPLYW_H
#include<list>
#include<vector>
#include<deque>
#include<iostream>
#include<cstdlib>
#include<algorithm>

class GrafGenerPrzeplyw
{
public:
  GrafGenerPrzeplyw();
  ~GrafGenerPrzeplyw();
  /**
   * @brief generujGraf Generuje normalny graf przepływowy. Wystepuja tam krawedzie powracjajace do wcześniejszych generacji.
   *        Ilosć wierzchołkow dla nGneracji z zakresu 2 do nGeneracji
   * @param nGeneracji Ilosc generacji. 
   */
  void generujGraf(const int nGeneracji, double value);
  
  /**
   * @brief generujGrafAcykliczny Graf przepływów bez krawedzi powracajacych do poprzednich generacji.
   *        Ilosć wierzchołkow dla nGneracji z zakresu 2 do nGeneracji
   * @param nGeneracji Ilosc generacji
   */
  void generujGrafAcykliczny(const int nGeneracji, const double value);
  
  /**
   * @brief generujGrafSkojarzen graf z dwiema generacjami.
   * @param maxWierzch Maksymalna ilosc wierzchołków w generacji.
   */
  void generujGrafSkojarzen(const int maxWierzch, const double value);
  
  /**
   * @brief getListeGeneracji W kazdej podliscie jest zestaw numerów wierchołkow które do niej nalezą. Pierwsza i ostatnia generacja 
   *        po jednym wierzchołku.
   * @return lista list wierzchołkow generacji.
   */
  std::list<std::list<int> >& getListeGeneracji(){return listGener;}
  
  /**
   * @brief getMacierzSasiedz zwraca boolowska macierz sasiedztwa
   * @return 
   */
  std::vector<std::vector<bool> >& getMacierzSasiedz(){return macierzSas;}

  void setnGeneracji(const int n);
  void setnWierz(const int n);
  void setListeGeneracji(std::list<std::list<int> > lista);
  void setMacierzSasiedz(std::vector<std::vector<bool> > mac);

private:
  void inicjujListeGeneracji(const int nGeneracji);
  void losujGeneracje(const int maxWierzch);
  void losujKrawedziePrzeplyw(const double value = 1);
  void losujKrawedzieCykliczne();
  void inicjujMacierzSas();
  std::list<std::list<int> > listGener;
  std::vector<std::vector<bool> > macierzSas;
  int _nGeneracji,_nWierz;
};

#endif // GRAFGENERPRZEPLYW_H
