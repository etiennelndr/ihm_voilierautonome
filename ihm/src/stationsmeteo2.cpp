#include "stationsmeteo2.h"
#include "ui_stationsmeteo2.h"
#include <iostream>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QtWidgets>
#include <balise_IHM.h>
#include "stationsmeteo2.h"
#include "mainwindow.h"


Stationsmeteo2::Stationsmeteo2(QWidget *parent, int nb) :
    QDialog(parent),
    ui(new Ui::stationsmeteo2)
{
    ui->setupUi(this);
    QVBoxLayout *grid = new QVBoxLayout;
    grid->addWidget(ui->BtnValider);
    for (unsigned int i = 0; i < nb; ++i) {
           labelsBalise.push_back(new QLabel(tr("----------------------------------- Station météo%1 ---------------------------------------").arg(i+1)));

           // ------ Longitude
           labelsLongitude.push_back(new QLabel(tr("Longitude")));
           lineEditsLongitude.push_back(new QLineEdit);
           grid->addWidget(labelsBalise.at(i));
           grid->addWidget(labelsLongitude.at(i));
           grid->addWidget(lineEditsLongitude.at(i));

           //------- Latitude
           labelsLatitude.push_back(new QLabel(tr("Latitude")));
           lineEditsLatitude.push_back(new QLineEdit);
           grid->addWidget(labelsLatitude.at(i));
           grid->addWidget(lineEditsLatitude.at(i));

           //------- ID
           labelsID.push_back(new QLabel(tr("ID")));
           lineEditsID.push_back(new QLineEdit);
           grid->addWidget(labelsID.at(i));

           grid->addWidget(lineEditsID.at(i));

       }

    this->setLayout(grid);

}

void Stationsmeteo2::on_BtnValider_clicked() {
    bool empty_longitude=false;
    for (unsigned int i=0; i<lineEditsLongitude.size();i++){
        if(lineEditsLongitude.at(i)->text().isEmpty())
            empty_longitude = true;
    }
    bool empty_latitude=false;
    for (unsigned int i=0; i<lineEditsLatitude.size();i++){
        if(lineEditsLatitude.at(i)->text().isEmpty())
            empty_latitude = true;
    }
    bool empty_id=false;
    for (unsigned int i=0; i<lineEditsID.size();i++){
        if(lineEditsID.at(i)->text().isEmpty())
            empty_id = true;

        MainWindow* mainWindow = new MainWindow(this,lineEditsID.at(i)->text().toInt());
    }
    if(!(empty_longitude ||
         empty_latitude  ||
         empty_id           )){
        Meteo* meteo;
        for (unsigned int i = 0; i < lineEditsID.size(); ++i) {
            meteo = new Meteo(int(stoi(lineEditsID.at(i)->text().toStdString())),float(stof(lineEditsLongitude.at(i)->text().toStdString())), float(stof(lineEditsLatitude.at(i)->text().toStdString())));
            emit new_meteo(*meteo);
        }
        meteo = new Meteo(-1,-1.0f,-1.0f);//Tell the mainwindow that the transfer of data is finished
        emit new_meteo(*meteo);
        this->close();
    }
    else{
        qDebug() << "Coucou";
    }



}

Stationsmeteo2::~Stationsmeteo2()
{
    delete ui;
}


