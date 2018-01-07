#include "grafrysujprzeplyw.h"
#include <time.h>
#include <utility>

GrafRysujPrzeplyw::GrafRysujPrzeplyw(QGraphicsScene *scene,const int h,const int w)
  :_scene(scene),_h(h),_w(w){
  
}
void GrafRysujPrzeplyw::rysujGraf(const std::list<std::list<int> > &listaGeneracji,const std::vector<std::vector<int> > &macierzWag,const bool skojarzenie){
  int wE=8,przesPunktu=4,sizeSas=macierzWag.size();
  _scene->clear();
  std::vector<std::pair<int,int> > points=getPointsLocation(listaGeneracji);
  QPen pen(Qt::black);
  QBrush brush(Qt::black);
  for(int i=skojarzenie;i<sizeSas-skojarzenie;i++){
      drawPointNumber(points.at(i),i);
      for(int j=skojarzenie;j<sizeSas-skojarzenie;j++){
          _scene->addEllipse(points.at(i).first-przesPunktu,points.at(i).second-przesPunktu,wE,wE,pen,brush);
          if(macierzWag[i][j]){
              pen.setWidth(ceil(macierzWag[i][j]/3));
              _scene->addLine(points.at(i).first,points.at(i).second,points.at(j).first,points.at(j).second,pen);
            }
        }
    }
  
}

void GrafRysujPrzeplyw::rysujGrafKolor(const std::list<std::list<int> > &listaGeneracji,const std::vector<std::vector<int> > &macierzWag,const std::vector<std::vector<bool> > &macierzPrzyp){
   bool skojarzenie = true;
  int wE=8,przesPunktu=4,sizeSas=macierzWag.size();
  _scene->clear();
  std::vector<std::pair<int,int> > points=getPointsLocation(listaGeneracji);
  QPen pen(Qt::black);
  QBrush brush(Qt::black);
  for(int i=skojarzenie;i<sizeSas-skojarzenie;i++){
      drawPointNumber(points.at(i),i);
      for(int j=skojarzenie;j<sizeSas-skojarzenie;j++){
          _scene->addEllipse(points.at(i).first-przesPunktu,points.at(i).second-przesPunktu,wE,wE,pen,brush);
          if(macierzWag[i][j]){
              pen.setWidth(ceil(macierzWag[i][j]/3));
              if(macierzPrzyp[i][j])
                  pen.setColor(Qt::green);
              _scene->addLine(points.at(i).first,points.at(i).second,points.at(j).first,points.at(j).second,pen);
              pen.setColor(Qt::black);

            }
        }
    }

}

void GrafRysujPrzeplyw::drawPointNumber(std::pair<int,int> pair,int i){
  std::stringstream str;
  str<<i;
  QGraphicsTextItem *text=_scene->addText(str.str().c_str(),QFont());
  text->setDefaultTextColor(Qt::black);
  text->setPos(pair.first,pair.second);
}

void GrafRysujPrzeplyw::drawEdgeInfo(std::pair<int,int> p1,std::pair<int,int> p2,const int i,const int j){
  std::stringstream str;
  str<<i<<"/"<<j<<std::endl;
  QGraphicsTextItem *text=_scene->addText(str.str().c_str(),QFont());
  text->setDefaultTextColor(Qt::black);
  text->setPos((p1.first+p2.first)/2,(p1.second+p2.second)/2);
}

std::vector<std::pair<int,int> > GrafRysujPrzeplyw::getPointsLocation(std::list<std::list<int> > listaGeneracji){
  std::vector<std::pair<int,int> >temp;
  int nGeneracji=listaGeneracji.size();
  int dx=_w/nGeneracji,przesX=-_w/2;
  for(std::list<std::list<int> >::iterator it=listaGeneracji.begin();it!=listaGeneracji.end();it++){
      int nWierzGener=it->size();
      int dy=_h/(nWierzGener+1);
      int przesY=-_h/2+dy;
      for(std::list<int>::iterator jt=it->begin();jt!=it->end();jt++){
          temp.push_back(std::make_pair<int,int>((int)przesX,(int)przesY));
          przesY+=dy;
        }
      przesX+=dx;
    }
  return temp;
}
