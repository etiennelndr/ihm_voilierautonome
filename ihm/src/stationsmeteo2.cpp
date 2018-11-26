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

\
stationsmeteo2::stationsmeteo2(QWidget *parent, int nb) :
    QDialog(parent),
    ui(new Ui::stationsmeteo2)
{

    ui->setupUi(this);
    void addWidget(QWidget * widget, int stretch = 2, Qt::Alignment alignment = 0);
    QVBoxLayout *grid = new QVBoxLayout;
    for (int i = 0; i <nb; ++i) {
           labelsBalise[i] = new QLabel(tr("----------------------------------- Station météo%1 ---------------------------------------").arg(i+1));
           // Longitude
           labels[i] = new QLabel(tr("Longitude"));
           lineEdits[i] = new QLineEdit;
           grid->addWidget(labelsBalise[i]);
           grid->addWidget(labels[i]);
           grid->addWidget(lineEdits[i]);
           //Latitude
           labels[i+1] = new QLabel(tr("Latitude"));
           lineEdits[i+1] = new QLineEdit;
           grid->addWidget(labels[i+1]);
           grid->addWidget(lineEdits[i+1]);
           //ID
           labelsID[i] = new QLabel(tr("ID"));
           lineEditsID[i] = new QLineEdit;
           grid->addWidget(labelsID[i]);

           grid->addWidget(lineEditsID[i]);
           this->setLayout(grid);

       }




}




stationsmeteo2::~stationsmeteo2()
{
    delete ui;
}


