#include "grafmaksprzeplyw.h"
#include <time.h>

GrafMaksPrzeplyw::GrafMaksPrzeplyw()
{
  
}

int GrafMaksPrzeplyw::znajdzMaksPrzeplyw(std::vector<std::vector<int> > macierzWag){
  int maks=0;
  std::list<int> tempList;
  std::vector<std::vector<int> > tempMacierzWag(macierzWag);  // Potrzebuje kopii bo będe zmieniał wartości wag.
  do{
      tempList=generujTrasePrzeplyw(tempMacierzWag);          // Znajduje najkrótsza trase pomiedzy zródłem a ujsciem. Przeszukiwanie wszerz.  
      if(tempList.size()>1){                                  // Czasami nie znajduje wogle trasy wiec wyrzuca wynik z poczatkowym elementem.
          int min=znajdzMinWage(tempList,tempMacierzWag);     // Iterujac po trasie znajduje minimalna wage.
          odwrocTrase(tempList,tempMacierzWag,min);           // Majac minimalna wagę wpisuje jej wartość na polach symetrycznych względem
          odejWageOdTrasy(tempList,tempMacierzWag,min);       // diagonali(krawedziach skierowanych w drugą stronę) z wyłaczeniem krawedzi 
          maks+=min;                                          // dostajacych do 1 i ostatniego wierzchołka. Potem odejmuje od normalnych
        }else{                                                // pol. Wartość min. dodaje do zliczania maksymalnego przepływu.
          break;
        }
    }while(!tempList.empty());                                
  generujMacierzPrzeplywu(macierzWag,tempMacierzWag);         // Tworze macierz gdzie będzie info o przepływie na danej krawedzi
  return maks;
}
std::vector<std::vector<int> > GrafMaksPrzeplyw::getMacierzPrzeplywu(){
  return macierzPrzeplywu;
}
int GrafMaksPrzeplyw::znajdzMinWage(std::list<int> trasa,std::vector<std::vector<int> >&macierzWag){
  int min=10;
  std::list<int>::iterator it=trasa.begin(),itNext=trasa.begin();
  itNext++;                                                   // Iteruje : --|it|itNext|---
  while(itNext!=trasa.end()){                                 // Waga pomiedzu 'it' i 'itNext'
      if(min>macierzWag[*it][*itNext]){                       
          min=macierzWag[*it][*itNext];
        }
      it++;itNext++;
    }
  return min;
}
void GrafMaksPrzeplyw::odejWageOdTrasy(std::list<int> trasa,std::vector<std::vector<int> >&macierzWag,const int waga){
  std::list<int>::iterator it=trasa.begin(),itNext=trasa.begin();
    itNext++;                                               // Iteruje : --|it|itNext|---
    while(itNext!=trasa.end()){                             // Odejmuje wagę minimalną znaleziona wczesniej 
        macierzWag[*it][*itNext]-=waga;                     // UWAGA. Błedy mogą tu być generowane. Ujemne wagi. Ale na razie nic nie wyszło.
        it++;itNext++;
      }
}
void GrafMaksPrzeplyw::odwrocTrase(std::list<int> trasa,std::vector<std::vector<int> >&macierzWag,const int waga){
      std::list<int>::iterator it=trasa.begin(),itNext=trasa.begin(),itLast=trasa.end();
      itNext++;itLast--;                // Iteruje begin()|it|itNext|---|---|---|itLast|end()
      it++;itNext++;
      while(itNext!=itLast){            // Iteruje tak by nie odwracać krawedzi poczatkowej i końcowej.
          std::cout<<(macierzWag.size())<<" "<<(*itNext)<<" "<<" | "<<(macierzWag.at(*itNext).size())<<" "<<(*it)<<std::endl;
           macierzWag[*itNext][*it]=waga;// W drugą strone skierowane.
          it++;itNext++;                // Jak w liscie było np 0-1-3-6. To wage przypisze tylko do (3,1)
        }                               // Dla scieżki 0-2-5-6-8 waga wpisana do (5,2) (6,5)
}
void GrafMaksPrzeplyw::generujMacierzPrzeplywu( std::vector<std::vector<int> > macierzWag, std::vector<std::vector<int> > macierzWagResult){
  int size=macierzWag.size();           // To jest zwykła róznica macierzy. Czasami są liczby ujemne ale to nas (chyba) nie interesuje.
  macierzPrzeplywu.clear();             
  for(int i=0;i<size;i++){
      macierzPrzeplywu.push_back(std::vector<int>());
      for(int j=0;j<size;j++){
          macierzPrzeplywu.at(i).push_back(macierzWag[i][j]-macierzWagResult[i][j]);
        }
    }
}
std::list<int> GrafMaksPrzeplyw::generujTrasePrzeplyw(std::vector<std::vector<int> > macierzWag){
  std::deque<std::list<int> > deque;  // Generuje najkrotsza trasę przepływu.
  std::list<int> temp;
  int size=macierzWag.size();
  temp.push_back(0);                    
  deque.push_back(temp);
  while(deque.empty()==false){
      temp=deque.front();
      deque.pop_front();
      int back=temp.back();
      if(back==size-1)                // Jeżeli ostatni element tworzonej listy jest tyle równy to oznacza że doszliśmy do ujścia. 
          return temp;
      for(int i=0;i<size;i++){        // Przechodze po wierszu macierzy sas.
          if(macierzWag[back][i]!=0&&std::find(temp.begin(),temp.end(),i)==temp.end()){
              temp.push_back(i);      // Jeżeli istniej krawedz z ostatniego elementu list temp do j oraz nie było j wcześniej na trasie.
              deque.push_back(temp);  // to dodaje j do listy i wrzucam na koniec kolejki.
              temp.pop_back();
            }
        }
    }
  return std::list<int>();
}

