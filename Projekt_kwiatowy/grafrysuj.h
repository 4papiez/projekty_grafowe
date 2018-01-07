#ifndef GRAFRYSUJ
#define GRAFRYSUJ
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <cmath>
#include "Graf.h"
#include <sstream>

/*Przykladowe użycie:
 * curr_graph.generujGrafKraw(7,5);
 * GrafRysuj gf(scene,70);
 * gf.rysuj(curr_graph);
 * Polecem GrafRysuj zastosowac podobnie co do Graf
 */
class GrafRysuj{
	public:
  		/**
  		 * @param scene
 		 * @param r Promien wokol ktorego bedą rozrzucone wierzchołki.
  		 * @throws std::runtime_error dla blednych argumentow
  		 */
 		 GrafRysuj(QGraphicsScene *scene,const double r);

  		/**
 		 * Wykonuje rysunek grafu na scenie w oparciu o zadana macierz sasiedztwa.
         * @param graf zainicjalizowany Graf
         * @throws std::runtime_error dla przypadku niezaicjalizowanego grafu.
  		 */
         void rysuj(GrafBase *graf,bool color = false, bool** tab = NULL);
        QPen& getPen(){return _pen;}
        QBrush& getBrush(){return _brush;}
      	double getR()const{return _r;}
        void setR(const double r){_r=r;}
        bool flag;
	private:
  		QGraphicsScene* _scene;
  		double _r;
  		QBrush _brush;
  		QPen _pen;
};

#endif // GRAFRYSUJ

