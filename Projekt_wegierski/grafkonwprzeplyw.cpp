#include "grafkonwprzeplyw.h"
#include <time.h>



GrafKonwPrzeplyw::GrafKonwPrzeplyw(const int val):MAX_VALUE(val)
{
   std::srand(time(NULL));
}

void GrafKonwPrzeplyw::konwersjaWagi(const std::vector<std::vector<bool> > macierzSas, const int val){
  MAX_VALUE = val;
  macierzWag.clear();
  int macierzSize=macierzSas.size();
  for(int i=0;i<macierzSize;i++){
      macierzWag.push_back(std::vector<int>());
      for(int j=0;j<macierzSize;j++){
          macierzWag.back().push_back((macierzSas.at(i).at(j))?(std::rand()%MAX_VALUE+1):(0));
        }
    }
}
void GrafKonwPrzeplyw::konwersjaWagiSkojarzenia(const std::vector<std::vector<bool> > macierzSas, const int val){
    MAX_VALUE = val;
  macierzWag.clear();
  int macierzSize=macierzSas.size();
  for(int i=0;i<macierzSize;i++){
      macierzWag.push_back(std::vector<int>());
      for(int j=0;j<macierzSize;j++){
          macierzWag.back().push_back((macierzSas.at(i).at(j))?(1):(0));
        }
    }
}
void GrafKonwPrzeplyw::konwersjaWagiSkojarzenia2(const std::vector<std::vector<bool> > macierzSas, const int val){
    MAX_VALUE = val;
    macierzWag.clear();
    int macierzSize=macierzSas.size();
    for(int i=0;i<macierzSize;i++){
        macierzWag.push_back(std::vector<int>());
        for(int j=0;j<macierzSize;j++){
            if (!i || !j || i==macierzSize-1 || j==macierzSize-1){
                macierzWag.back().push_back((macierzSas.at(i).at(j))?(MAX_VALUE):(0));
            }else{
                macierzWag.back().push_back((macierzSas.at(i).at(j))?(std::rand()%MAX_VALUE+1):(0));
            }

        }
    }

}

