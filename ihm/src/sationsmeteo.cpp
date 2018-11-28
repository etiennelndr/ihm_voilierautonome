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
    Stationsmeteo2* stationsmeteo2 = new Stationsmeteo2(nullptr,spin1);
    stationsmeteo2->setModal(true);
    stationsmeteo2->exec();
}


