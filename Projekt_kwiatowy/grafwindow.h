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

#include "Graf.h"
#include "grafrysuj.h"
#include "GGenerator.h"
#include "GGeneratorVE.h"
#include "BlossomMatching.h"


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
  void StartDrawing(bool color=false, bool** btab = NULL);
  void generuj();
private slots:
  void on_skojarzenieButton_clicked();
  void importGraf();
  
  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

  void on_skojarzenieButton_2_clicked();

  void on_skojarzenieButton_3_clicked();

  void on_checkBox_stateChanged(int arg1);

private:
  Ui::GrafWindow *ui;
  QGraphicsScene* scene;
  bool status;
  Graf* curr_graph;
  GrafRysuj *gf;
};

#endif // GRAFWINDOW_H
