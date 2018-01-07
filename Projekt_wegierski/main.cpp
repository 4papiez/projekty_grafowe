#include "grafwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  GrafWindow w;
  w.show();
  
  return a.exec();
}
