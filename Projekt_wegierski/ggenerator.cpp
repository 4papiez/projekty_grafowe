#include "ggenerator.h"
#include "ui_ggenerator.h"


GGenerator::GGenerator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GGenerator),
    isRejected(false)
{
    ui->setupUi(this);
    setWindowTitle("Dodatkowy parametr");
}

GGenerator::~GGenerator()
{
    delete ui;
}

double GGenerator::on_buttonBox_accepted()
{
  return this->ui->doubleSpinBox->value();
}

void GGenerator::on_buttonBox_rejected()
{
    isRejected = true;
}
