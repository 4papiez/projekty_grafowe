#include "GGenerator.h"
#include "ui_ggenerator.h"


GGenerator::GGenerator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GGenerator),
    isRejected(false)
{
    ui->setupUi(this);
    setWindowTitle("Losuj Graf");
}

GGenerator::~GGenerator()
{
    delete ui;
}

std::pair<int, double> GGenerator::on_buttonBox_accepted()
{
  return std::pair<int,double>(this->ui->spinBox->value(),this->ui->doubleSpinBox->value());
}

void GGenerator::on_buttonBox_rejected()
{
    isRejected = true;
}
