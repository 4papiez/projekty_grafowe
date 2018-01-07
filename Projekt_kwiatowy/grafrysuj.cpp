#include "grafrysuj.h"


GrafRysuj::GrafRysuj(QGraphicsScene *scene,const double r)
  	:_scene(scene),_r(r),_brush(Qt::black),_pen(Qt::black){
  	if(scene==0||scene==NULL)
   		throw std::runtime_error("GrafRysuj::GrafRysuj : Blad scene");
        if(r<=0)
    	throw std::runtime_error("GrafRysuj::GrafRysuj : Blad promienia");
    this->flag = false;
}
//----------------------------------------------------
void GrafRysuj::rysuj(GrafBase *graf,bool color,bool** btab){
    if(graf->init()==false)
    throw std::runtime_error(" GrafRysuj::rysuj : Niezainicjalizowany graf");
    int n=graf->getN(),w=8;
    int** tab=graf->getTab();
    double d=(2*M_PI)/n,temp=M_PI/2;
  	_scene->clear();
  	for(int i=0;i<n;i++){
       	_scene->addEllipse(std::sin(i*d+temp)*_r,std::cos(i*d+temp)*_r,w,w,_pen,_brush);
        std::stringstream str;str<<i;
        QGraphicsTextItem *text=_scene->addText(str.str().c_str(),QFont());
       	text->setDefaultTextColor(Qt::black);
        text->setPos(std::sin(i*d+temp)*(_r+15)-w,std::cos(i*d+temp)*(_r+15)-w);
      	for(int j=i+1;j<n;j++){
            std::stringstream str1;
            if(tab[i][j] && this->flag)
                str1<<tab[i][j];
            QGraphicsTextItem *text1=_scene->addText(str1.str().c_str(),QFont());
            if (color){
                if (btab[i][j]) {
                    _pen.setColor(Qt::green);
                    text1->setDefaultTextColor(Qt::green);
                }
                else {
                    _pen.setColor(Qt::black);
                    text1->setDefaultTextColor(Qt::red);
                }
            }
                if(tab[i][j]){
                    _scene->addLine(std::sin(i*d+temp)*_r+w/2,std::cos(i*d+temp)*_r+w/2,std::sin(j*d+temp)*_r+w/2,std::cos(j*d+temp)*_r+w/2,_pen);
                    qreal q01 = (std::sin(j*d+temp)*_r+w/2);
                    qreal q02 = (std::cos(j*d+temp)*_r+w/2 + 15);
                    qreal q1 = ((std::sin(i*d+temp)*_r+w/2) + (std::sin(j*d+temp)*_r+w/2 + 15))/2;
                    qreal q2 = ((std::cos(i*d+temp)*_r+w/2)+ (std::cos(j*d+temp)*_r+w/2 + 15))/2;
                    text1->setPos( (q1 + q01)/2, (q2 + q02)/2 );
                    text1->setDefaultTextColor(Qt::red);


                }
    	}
  	}
    _pen.setColor(Qt::black);

}

