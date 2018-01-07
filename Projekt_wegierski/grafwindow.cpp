#include "grafwindow.h"
#include "ui_grafwindow.h"
#include <string>
#include <sstream>
#include <iostream>


int suma(int x){
    if(x>0)
        return x +suma(x-1);
    else return 0;
}

void GrafWindow::zapiszGraf(const std::string str, std::vector<std::vector<int> > tab, const int n, const int l)const{
  std::fstream plik;
  plik.open(str.c_str(),std::ios::out);
  if(n<=0||l<0)
      throw  std::runtime_error("Graf::zapiszGraf : Bład argumentu");
  if( plik.good() == false)
      throw std::runtime_error("Graf::zapiszGraf : Bład pliku");
  plik<<(n-2)<<" "<<l<<std::endl;
  for(int i=1;i<n-1;i++){
      for(int j=i+1;j<n-1;j++){
              plik<<i<<" "<<j<<" "<<tab[i][j]<<std::endl;

      }
  }
  plik.close();
}



void GrafWindow::zapiszGraf(const std::string str)const{
  int size = gkp->getMacierzWag().size();
  zapiszGraf(str,gkp->getMacierzWag(),size, (*(++(ggp->getListeGeneracji().begin()))).size());
}

void GrafWindow::importGraf(){
    QString directory=QFileDialog::getOpenFileName(this,tr("Select file to import"),"/home/","*.graf");
    try{
      //curr_graph->generujGrafPlik(directory.toStdString());
        std::fstream plik;
        ggp->generujGrafSkojarzen(ui->spinBox_2->value(), 1);
        gkp->konwersjaWagiSkojarzenia2(ggp->getMacierzSasiedz(),ui->spinBox->value());
        int n,l,ii,jj,ww;
        std::vector<std::vector<int> > mac = gkp->getMacierzWag();
        std::list<std::list<int>> lista = ggp->getListeGeneracji();
        std::vector<std::vector<bool> > mac2 = ggp->getMacierzSasiedz();
        mac.clear();
        lista.clear();
        mac2.clear();

        plik.open(directory.toStdString().c_str(),std::ios::in);
        if( plik.good() == true )
           {
               plik >> n;
               n+=2;
               plik >> l;
               for(int i=0;i<n;i++){
                   mac.push_back(std::vector<int>());
                   mac2.push_back(std::vector<bool>());
                   for(int j=0;j<n;j++)
                       mac.back().push_back(0);
                       mac2.back().push_back(0);
               }
                for(int i=0;i<suma(n);++i){
                    plik >> ii;
                    plik >> jj;
                    plik >> ww;
                    mac[ii][jj]=ww;
                    mac2[ii][jj]=ww?1:0;
                }
                for(int i=0;i<4;++i)
                    lista.push_back(std::list<int>());
                std::list<std::list<int> >::iterator it = lista.begin();



                it->push_back(0);
                it++;
                for (int i=1;i<=l;++i)
                    it->push_back(i);
                it++;
                for(int i=l+1;i<n-1;++i)
                    it->push_back(i);
                lista.back().push_back(n-1);

                ggp->setListeGeneracji(lista);
                ggp->setMacierzSasiedz(mac2);
                ggp->setnGeneracji(2);
                ggp->setnWierz(n-1);
                gkp->setMacierzWag(mac);
               plik.close();
           }
      QMessageBox::information(0,"success",(std::to_string(lista.size())).c_str());
      grp->rysujGraf(ggp->getListeGeneracji(),gkp->getMacierzWag(),true);
        znajdzPrzeplyw();
    }catch(...){
      QMessageBox::information(0, "error","No file loaded");
    }

}

GrafWindow::GrafWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::GrafWindow)
{
  ui->setupUi(this);
  
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  scene->setBackgroundBrush(Qt::lightGray);
  this->setWindowTitle("Algorytm Węgierski");

  ggp=new GrafGenerPrzeplyw();
  grp=new GrafRysujPrzeplyw(scene,600,800);
  gkp=new GrafKonwPrzeplyw(ui->spinBox->value());
 // gmp=new GrafMaksPrzeplyw();

}

GrafWindow::~GrafWindow()
{
  delete ui;
  delete scene;
  delete ggp;
  delete grp;
  delete gkp;
}

void GrafWindow::generuj(){
  try{


    ggp->generujGraf(ui->spinBox->value(),1);
    gkp->konwersjaWagi(ggp->getMacierzSasiedz(), ui->spinBox->value());
    grp->rysujGraf(ggp->getListeGeneracji(),gkp->getMacierzWag(),false);
    znajdzPrzeplyw();
    std::stringstream str;str<<"Nie ma";
    std::vector<std::vector<int> > macierzPrzepl = gkp->getMacierzWag();

    ui->textBrowser_2->setText(str.str().c_str());
    }catch(...){
        QMessageBox::information(0, "error","Bład generacji");
     }
}

void GrafWindow::ZapiszGraF(){
    {
      QString directory=QFileDialog::getSaveFileName(this,"Zapis","/home/","*.graf");
       try{
        zapiszGraf(directory.toStdString());
      }catch(...){
        QMessageBox::information(0, "error","Bład zapisu");
      }
    }

}


void GrafWindow::on_skojarzenieButton_clicked()
{
  try{
    double value = 1;
    GGenerator gen;
    gen.setModal(true);
    gen.exec();
    if(!gen.isRejected)
        value = gen.on_buttonBox_accepted();
    ggp->generujGrafSkojarzen(ui->spinBox_2->value(),value);
    gkp->konwersjaWagiSkojarzenia2(ggp->getMacierzSasiedz(),ui->spinBox->value());
    grp->rysujGraf(ggp->getListeGeneracji(),gkp->getMacierzWag(),true);
    znajdzPrzeplyw();
  }catch(...){
   std::cout<<"skojarzenie"<<std::endl; 
  }
    std::stringstream str;str<<"Nie ma";
    std::vector<std::vector<int> > macierzPrzepl = gkp->getMacierzWag();

    ui->textBrowser_2->setText(str.str().c_str());
}

void GrafWindow::znajdzPrzeplyw(){
    vector<vector<bool>> MacPrzyp;
    znajdzPrzeplyw(false, MacPrzyp);
}


void GrafWindow::znajdzPrzeplyw(bool flag, vector<vector<bool>> MacPrzyp){
  try{
    
    std::vector<std::vector<int> >vec=gkp->getMacierzWag();
    int ile = vec.size()-1;
    ui->textBrowser->clear();
    int i=0,j=0;
    for(std::vector<std::vector<int> >::iterator it=vec.begin();it!=vec.end();it++,i++,j=0){
        for(std::vector<int>::iterator jt=it->begin();jt!=it->end();jt++,j++){
            if((*jt)!=0 && i && j<ile && i<j){
                if(flag)
                    if (MacPrzyp[i][j])
                        ui->textBrowser->setTextColor(Qt::green);
                std::stringstream str;str<<i<<" -> "<<j<<" | W: "<<(*jt);
                ui->textBrowser->append(QString(str.str().c_str()));
                ui->textBrowser->setTextColor(Qt::black);
              }
          }
      }
  }catch(...){
   std::cout<<"wagi"<<std::endl; 
  }
}




void GrafWindow::on_pushButton_2_clicked()
{
    ZapiszGraF();
}

void GrafWindow::on_pushButton_clicked()
{
    importGraf();
}

void GrafWindow::on_skojarzenieButton_2_clicked()
{
    try{
       vector<vector<int>> temp(gkp->getMacierzWag());
       vector<vector<double>> temp2;
       for(unsigned int i=0;i<temp.size();i++)
           temp2.push_back(vector<double> (temp[i].begin(),temp[i].end()));
      W_algorytm algo(temp2,(*(++(ggp->getListeGeneracji().begin()))).size());
      vector<vector<bool>> MacPrzyp = algo.get_PrzypisanieMac();
      int wynik = algo.get_wynik();
      grp->rysujGrafKolor(ggp->getListeGeneracji(),gkp->getMacierzWag(),MacPrzyp);
      std::string s = std::to_string(wynik);
      ui->textBrowser_2->setText(QString(s.c_str()));
      znajdzPrzeplyw(true,MacPrzyp);
    }catch(...){
     std::cout<<"skojarzenie"<<std::endl;
    }
}
