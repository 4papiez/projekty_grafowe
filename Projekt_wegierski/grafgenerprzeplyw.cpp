#include "grafgenerprzeplyw.h"
#include <time.h>

GrafGenerPrzeplyw::GrafGenerPrzeplyw(){
  std::srand(time(NULL));
}

GrafGenerPrzeplyw::~GrafGenerPrzeplyw(){

}


void GrafGenerPrzeplyw::setnGeneracji(const int n){
    this->_nGeneracji = n;
}
void GrafGenerPrzeplyw::setnWierz(const int n){
    this->_nWierz = n;
}
void GrafGenerPrzeplyw::setListeGeneracji(std::list<std::list<int> > lista){
    this->listGener = lista;
}
void GrafGenerPrzeplyw::setMacierzSasiedz(std::vector<std::vector<bool> > mac){
    this->macierzSas = mac;
}

void GrafGenerPrzeplyw::inicjujListeGeneracji(const int nGeneracji){
  listGener.clear();                        // Usuwam pozostałosci po ostatnio generowanym grafie.
  macierzSas.clear();                       
  _nGeneracji=nGeneracji;
  _nWierz=0;
  for(int i=0;i<nGeneracji+2;i++){          // Lista list wiec musze zacząć listy dla każdej generacji
      listGener.push_back(std::list<int>());
    }
}

void GrafGenerPrzeplyw::generujGraf(const int nGeneracji, const double value){
  generujGrafAcykliczny(nGeneracji, value);        // Graf przeplywowy jest rozszerzeniem grafu acykilcznego o krawedzie
  losujKrawedzieCykliczne();                // powracające, tworzace cykle.
}


void GrafGenerPrzeplyw::generujGrafSkojarzen(const int maxWierzch, const double value){
  inicjujListeGeneracji(2);                 // Zawsze dwie generacje bo to skojarzenia.
  losujGeneracje(maxWierzch);               // Loswanie wierzchołków dla każdej generacji
  inicjujMacierzSas();
  losujKrawedziePrzeplyw(value);
}

void GrafGenerPrzeplyw::generujGrafAcykliczny(const int nGeneracji, double value){
  inicjujListeGeneracji(nGeneracji);        // Usuniecie poprzedniego grafu i stworzenie miejsca na nowy.
  losujGeneracje(nGeneracji);                         // Loswanie wierzchołków dla każdej generacji
  inicjujMacierzSas();
  losujKrawedziePrzeplyw(value);
}

void GrafGenerPrzeplyw::losujGeneracje(const int maxWierzch){
  listGener.front().push_back(_nWierz++);   // Dodaje do pierwszej generacji wierzchołek 0.
  std::list<std::list<int> >::iterator it=listGener.begin(),itE=listGener.end();
  it++;itE--;                               // Iteratory ustawione tak by ominać pierwszy i ostatni wierzchołek bo mają mieć osobne
  for(;it!=itE;it++){                       // generacje. Liczba wierzcholkow od 2 do ilosci generacji.
      int nWierzGener=std::rand()%(maxWierzch-1)+2;
      for(int i=0;i<nWierzGener;i++){
          it->push_back(_nWierz++);
        }
    }
  listGener.back().push_back(_nWierz++);    // Ostatni wierz do ostatniej generacji samotnie.
}

void GrafGenerPrzeplyw::inicjujMacierzSas(){
  for(int i=0;i<_nWierz;i++){               // Wypelniam zerami (false) cała macierz sasiedztwa.
      macierzSas.push_back(std::vector<bool>());
      for(int j=0;j<_nWierz;j++){
          macierzSas.back().push_back(0);
        }
    }
}

void GrafGenerPrzeplyw::losujKrawedziePrzeplyw(double value){
    std::vector<int> firstgen {std::begin(*(++listGener.begin())), std::end(*(++listGener.begin()))};
    std::vector<int> secondgen {std::begin(*(++(++(listGener.begin())))), std::end(*(++(++(listGener.begin()))))};
  for (unsigned int i = 0; i<firstgen.size();i++)
      for(unsigned int j = 0; j<secondgen.size();j++)
          if(((double)(std::rand()%1000))/1000<value)
             macierzSas[firstgen[i]][secondgen[j]] =  macierzSas[secondgen[j]][firstgen[i]] =true;


}


void GrafGenerPrzeplyw::losujKrawedzieCykliczne(){
  for(int i=0;i<2*_nGeneracji;i++){
      int n1,n2;
      int limit=0;
      do{
          n1=std::rand()%(_nWierz-1);       // Punkt startowy - wszytkie oprócz ostatniego wierzchołka "spływu"  
          n2=std::rand()%(_nWierz-1)+1;     // Punkt koncowy - wszystkie oprócz pierwszego "wypływu"
          limit++;                          // Limit bo może być za pełno w macierzy. Na wszelki wypadek.
        }while((macierzSas[n1][n2]==true||n1==n2||macierzSas[n2][n1]==true)&&limit<_nWierz*_nWierz);
      macierzSas[n1][n2]=true;
    }
}

