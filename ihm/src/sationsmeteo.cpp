#include "sationsmeteo.h"
#include "ui_sationsmeteo.h"
#include "mainwindow.h"

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
    Stationsmeteo2* stationsmeteo2 = new Stationsmeteo2(this,spin1);

    MainWindow* stt = new MainWindow(this,spin1);
    stationsmeteo2->setModal(true);
    stationsmeteo2->show();
    connect(stationsmeteo2, SIGNAL(new_meteo(Meteo)), this, SLOT(transfer_new_meteo(Meteo)));
}

void sationsmeteo::transfer_new_meteo(Meteo m){
    emit new_meteo(m);
}


