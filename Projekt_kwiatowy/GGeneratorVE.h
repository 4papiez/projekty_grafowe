#ifndef GGENERATORVE_H
#define GGENERATORVE_H

#include <QDialog>
#include <utility>
#include "Graf.h"

namespace Ui {
class GGeneratorVE;
}

class GGeneratorVE : public QDialog
{
    Q_OBJECT

public:
    friend class Gdraw;
    explicit GGeneratorVE(QWidget *parent = 0);
    ~GGeneratorVE();
     std::pair<int,int> on_buttonBox_accepted();
     bool isRejected;
private slots:

    void update();

    void on_buttonBox_rejected();

private:
    Ui::GGeneratorVE *ui;

};

#endif // GGENERATORVE_H
