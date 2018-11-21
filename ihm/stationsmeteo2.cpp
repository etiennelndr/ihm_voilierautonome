#include "stationsmeteo2.h"
#include "ui_stationsmeteo2.h"
#include <iostream>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QtWidgets>

\
stationsmeteo2::stationsmeteo2(QWidget *parent, int nb) :
    QDialog(parent),
    ui(new Ui::stationsmeteo2)
{

    ui->setupUi(this);
    void addWidget(QWidget * widget, int stretch = 2, Qt::Alignment alignment = 0);
    QVBoxLayout *grid = new QVBoxLayout;
    for (int i = 0; i <nb; ++i) {
           labelsBalise[i] = new QLabel(tr("----------------------------------- Balise%1 ---------------------------------------").arg(i+1));
           labels[i] = new QLabel(tr("Longitude"));
           lineEdits[i] = new QLineEdit;
           grid->addWidget(labelsBalise[i]);
           grid->addWidget(labels[i]);
           grid->addWidget(lineEdits[i]);
           labels[i+1] = new QLabel(tr("Latitude"));
           lineEdits[i+1] = new QLineEdit;
           grid->addWidget(labels[i+1]);
           grid->addWidget(lineEdits[i+1]);
           this->setLayout(grid);

       }



}




stationsmeteo2::~stationsmeteo2()
{
    delete ui;
}


