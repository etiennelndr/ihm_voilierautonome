#include "sationsmeteo.h"
#include "ui_sationsmeteo.h"
#include "stationsmeteo2.h"

sationsmeteo::sationsmeteo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sationsmeteo)
{
    ui->setupUi(this);
}

sationsmeteo::~sationsmeteo()
{
    delete ui;
}

void sationsmeteo::on_pushButton_clicked()
{
    this->close();
    int spin1 = ui->SpinMeteo->value();
    stationsmeteo2* Stationsmeteo2 = new stationsmeteo2(nullptr,spin1);
    Stationsmeteo2->setModal(true);
    Stationsmeteo2->exec();


}


