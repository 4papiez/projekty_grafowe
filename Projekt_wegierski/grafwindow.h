#ifndef GRAFWINDOW_H
#define GRAFWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTableWidget>
#include <QListWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include <iostream>
#include <fstream>
#include <vector>

#include "w_algorytm.h"
#include "grafgenerprzeplyw.h"
#include "grafrysujprzeplyw.h"
#include "grafkonwprzeplyw.h"
//#include "grafmaksprzeplyw.h"

#include "ggenerator.h"

namespace Ui {
  class GrafWindow;
}

class GrafWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit GrafWindow(QWidget *parent = 0);
  ~GrafWindow();
  
public slots:
  void generuj();
  void ZapiszGraF();
private slots:
  void on_skojarzenieButton_clicked();
  void zapiszGraf(const std::string str)const;
  void zapiszGraf(const std::string str, std::vector<std::vector<int>> tab,const int n,const int l)const;
  void importGraf();
  
  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

  void on_skojarzenieButton_2_clicked();

private:
  void znajdzPrzeplyw(bool flag, vector<vector<bool>> MacPrzyp);
  void znajdzPrzeplyw();
  Ui::GrafWindow *ui;
  QGraphicsScene* scene;
  GrafGenerPrzeplyw *ggp;
  GrafRysujPrzeplyw *grp;
  GrafKonwPrzeplyw *gkp;
  //GrafMaksPrzeplyw *gmp;
};

#endif // GRAFWINDOW_H
