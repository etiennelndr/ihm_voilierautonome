#include "balise_IHM.h"
#include "ui_balises.h"

balises::balises(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::balises)
{
    ui->setupUi(this);

    delete ui;

}



void balises::on_bouton_valider_clicked()
{

}
