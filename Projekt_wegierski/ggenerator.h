#ifndef GGENERATOR_H
#define GGENERATOR_H

#include <QDialog>
#include <utility>
#include <iostream>

namespace Ui {
class GGenerator;
}

class GGenerator : public QDialog
{
    Q_OBJECT

public:
    friend class Gdraw;
    explicit GGenerator(QWidget *parent = 0);
    ~GGenerator();
    bool isRejected;
    double on_buttonBox_accepted();
private slots:


    void on_buttonBox_rejected();

private:
    Ui::GGenerator *ui;

};

#endif // GGENERATOR_H
