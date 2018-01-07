#ifndef GRAFRYSUJPRZEPLYW_H
#define GRAFRYSUJPRZEPLYW_H
#include "grafkonwprzeplyw.h"
#include <cmath>
#include<QGraphicsScene>
#include<QGraphicsTextItem>
#include<sstream>

class GrafRysujPrzeplyw
{
public:
  GrafRysujPrzeplyw(QGraphicsScene *scene,const int h,const int w);
  void rysujGraf(const std::list<std::list<int> > &listaGeneracji, const std::vector<std::vector<int> > &macierzSas, const bool skojarzenie);
  //void rysujGrafSkojarzenia(const std::list<std::list<int> > &listaGeneracji, const std::vector<std::vector<bool> > &macierzSas);
  void rysujGrafKolor(const std::list<std::list<int> > &listaGeneracji,const std::vector<std::vector<int> > &macierzWag,const std::vector<std::vector<bool> > &macierzPrzyp);
private:
  std::vector<std::pair<int,int> > getPointsLocation(std::list<std::list<int> > listaGeneracji);
  void drawPointNumber(std::pair<int,int> pair,int i);
  void drawEdgeInfo(std::pair<int,int> p1, std::pair<int,int> p2, const int i, const int j);
  QGraphicsScene *_scene;
  int _h,_w;
};

#endif // GRAFRYSUJPRZEPLYW_H
