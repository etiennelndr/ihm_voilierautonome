#include "stationmeteo2.h"
#include "ui_stationmeteo2.h"

stationMeteo2::stationMeteo2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stationMeteo2)
{
    ui->setupUi(this);
}

stationMeteo2::~stationMeteo2()
{
    delete ui;
}
