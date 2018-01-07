#include "GGeneratorVE.h"
#include "ui_ggeneratorve.h"

GGeneratorVE::GGeneratorVE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GGeneratorVE),
    isRejected(false)
{
    ui->setupUi(this);
    setWindowTitle("Generuj Graf");
}

GGeneratorVE::~GGeneratorVE()
{
    delete ui;
}

std::pair<int,int> GGeneratorVE::on_buttonBox_accepted()
{
    return std::pair<int,int>(this->ui->spinBox_2->value(),this->ui->spinBox->value());
}

void GGeneratorVE::update(){
  ui->spinBox->setMaximum(Graf::maksIloscKrawedzi(ui->spinBox_2->value()));
}

void GGeneratorVE::on_buttonBox_rejected()
{
    isRejected = true;
}
