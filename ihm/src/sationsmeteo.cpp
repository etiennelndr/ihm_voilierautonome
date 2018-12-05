#include "sationsmeteo.h"
#include "ui_sationsmeteo.h"
#include "mainwindow.h"

/**
 * CONSTRUCTOR
 *
 * @brief StationsMeteo::StationsMeteo : TODO
 * @param parent
 */
StationsMeteo::StationsMeteo(QWidget *parent) : QDialog(parent), ui(new Ui::StationsMeteo) {
    ui->setupUi(this);
}

/**
 * DESTRUCTOR
 *
 * @brief StationsMeteo::~StationsMeteo : TODO
 */
StationsMeteo::~StationsMeteo() {
    delete ui;
}

/**
 * SLOT -> TODO
 *
 * @brief StationsMeteo::on_pushButton_clicked : TODO
 */
void StationsMeteo::on_pushButton_clicked() {
    this->close();
    int spin1 = ui->SpinMeteo->value();
    Stationsmeteo2* stationsmeteo2 = new Stationsmeteo2(this,spin1);
    stationsmeteo2->setModal(true);
    stationsmeteo2->show();
    connect(stationsmeteo2, SIGNAL(new_meteo(Meteo)), this, SLOT(transfer_new_meteo(Meteo)));
}

/**
 * SLOT -> TODO
 *
 * @brief StationsMeteo::transfer_new_meteo : TODO
 * @param m
 */
void StationsMeteo::transfer_new_meteo(Meteo m){
    emit new_meteo(m);
}


