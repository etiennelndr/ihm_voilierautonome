#include "balises.h"
#include "ui_balises.h"

balises::balises(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::balises)
{
    ui->setupUi(this);
}

balises::~balises()
{
    delete ui;
}
