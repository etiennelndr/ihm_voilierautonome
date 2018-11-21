#include "sationsmeteo.h"
#include "ui_sationsmeteo.h"

sationsmeteo::sationsmeteo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SationsMeteo)
{
    ui->setupUi(this);
}

sationsmeteo::~sationsmeteo()
{
    delete ui;
}
