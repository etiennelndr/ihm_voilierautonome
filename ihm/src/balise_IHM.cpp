#include "balise_IHM.h"
#include "ui_Balise_IHM.h"
#include <QDebug>
#include <balise.h>

Balise_IHM::Balise_IHM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Balise_IHM)
{
    ui->setupUi(this);

    delete ui;

}


/*void Balise_IHM::AffichageBateaux()
{
    qDebug() << "hehe";
}*/

void Balise_IHM::on_BtnValider_clicked()
{
  // balisee = new Balise(this);


}
