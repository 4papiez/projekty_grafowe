#include "grafwindow.h"
#include "ui_grafwindow.h"
#include <string>
#include <sstream>
#include <iostream>


void GrafWindow::importGraf(){
    QString directory=QFileDialog::getOpenFileName(this,tr("Select file to import"),"/home/","*.graf");
    try{
        curr_graph->generujGrafPlik(directory.toStdString());
        QMessageBox::information(0,"success","File loaded properly \n Ready to draw");
    }catch(...){
        QMessageBox::information(0, "error","No file loaded");
    }
    StartDrawing();
}

GrafWindow::GrafWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::GrafWindow)
{
  ui->setupUi(this);
  status=false;
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  scene->setBackgroundBrush(Qt::lightGray);
  this->setWindowTitle("Algorytm Kwiatowy");

  curr_graph=new Graf();
  gf=new GrafRysuj(scene,300);

}

GrafWindow::~GrafWindow()
{
  delete curr_graph;
  delete gf;

}

void GrafWindow::generuj(){
    GGeneratorVE gen;
        gen.setModal(true);
        gen.exec();
        if(!gen.isRejected){
        std::pair<int,int> ve_count = gen.on_buttonBox_accepted();
        try{
            this->curr_graph->generujGrafKraw(ve_count.first,ve_count.second,ui->spinBox->value());
            StartDrawing();
        }
        catch(...){
            QMessageBox::information(0, "error","Bład generacji");
        }
        }

}

void GrafWindow::StartDrawing(bool color, bool** btab){
  try{
    ui->textBrowser->clear();
    gf->rysuj(curr_graph,color,btab);
    int ** tab = curr_graph->getTab();
    int n = curr_graph->getN();

    for(int i=0, j=0;i<n;i++,j=0){
        for(j=i;j<n;j++){
            if(tab[i][j]){
                if (color){
                    if(btab[i][j]) ui->textBrowser->setTextColor(Qt::darkGreen);
                    else ui->textBrowser->setTextColor(Qt::black);
                }
                std::stringstream str;str<<i<<" -> "<<j<<" | W: "<<tab[i][j];
                ui->textBrowser->append(QString(str.str().c_str()));
            }
        }
    }
    ui->textBrowser->setTextColor(Qt::black);
  }catch(...){
    QMessageBox::information(0, "error","Blad grafu");
  }
}


void GrafWindow::on_skojarzenieButton_clicked()
{
    GGenerator gen;
    gen.setModal(true);
    gen.exec();
    if(!gen.isRejected){
    std::pair<int,double> values = gen.on_buttonBox_accepted();
    try{
     this->curr_graph->generujGrafPrawd(values.first,values.second,ui->spinBox->value());
      StartDrawing();

    }catch(...){
      QMessageBox::information(0, "error","Bład generacji");
    }
    }
}




void GrafWindow::on_pushButton_2_clicked()
{
    QString directory=QFileDialog::getSaveFileName(this,"Zapis","/home/","*.graf");
       try{
        curr_graph->zapiszGraf(directory.toStdString());
      }catch(...){
        QMessageBox::information(0, "error","Bład zapisu");
      }
}

void GrafWindow::on_pushButton_clicked()
{
    importGraf();
}

void GrafWindow::on_skojarzenieButton_2_clicked()
{
    int n=curr_graph->getN();
    int** tab = curr_graph->getTab();
    BlossomMatching matching(n);
        for (int i = 0; i < n; i++){
            for(int j=i;j<n;j++){
                if(tab[i][j])
                    matching.add_edge(i,j, tab[i][j]);
            }
        }
        bool success = matching.find_min_cost_matching();
        if (success)
        {
            ui->textBrowser_2->setTextColor(Qt::darkGreen);
        }else{
             ui->textBrowser_2->setTextColor(Qt::red);
        }

        int wynik = matching.get_cost_from_matching();
        std::string s = std::to_string(wynik);
        ui->textBrowser_2->setText(QString(s.c_str()));
        auto edges = matching.get_matched_edges();
        bool** tab_flaga = new bool*[n];
        for (int i=0;i<n;i++)
            tab_flaga[i]=new bool[n];
        for (int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                tab_flaga[i][j] = false;
        for(auto e:edges)
           tab_flaga[e.first][e.second]=tab_flaga[e.second][e.first]=true;
        StartDrawing(true, tab_flaga);


         for (int i=0;i<n;i++)
             delete[] tab_flaga[i];
         delete[] tab_flaga;
         status = true;

}

void GrafWindow::on_skojarzenieButton_3_clicked()
{
    generuj();
}

void GrafWindow::on_checkBox_stateChanged(int arg1)
{
    gf->flag = arg1;
    if(status)
        GrafWindow::on_skojarzenieButton_2_clicked();
    else
         StartDrawing();
}
