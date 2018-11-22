#include "balise_IHM.h"
#include "ui_Balise_IHM.h"

Balise_IHM::Balise_IHM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Balise_IHM)
{
    ui->setupUi(this);

    delete ui;

}



void Balise_IHM::on_bouton_valider_clicked()
{

}
