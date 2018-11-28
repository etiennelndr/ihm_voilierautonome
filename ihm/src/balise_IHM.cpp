#include "balise_IHM.h"
#include "ui_Balise_IHM.h"

Balise_IHM::Balise_IHM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Balise_IHM)
{
    ui->setupUi(this);
    connect(ui->BtnValider, SIGNAL(clicked()), this, SLOT(on_BtnValider_clicked()));

    delete ui;

}


/*void Balise_IHM::AffichageBateaux()
{
    qDebug() << "hehe";
}*/

void Balise_IHM::on_BtnValider_clicked()
{
    if(ui->TxtLatitude_1->text()!=ui->TxtLongitude_1->text() && ui->TxtLatitude_1->text()!="" && ui->TxtLongitude_1->text()!=""){
        Balise* balise = new Balise(float(stof(ui->TxtLatitude_1->text().toStdString())), float(stof( ui->TxtLongitude_1->text().toStdString())));
        //emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_2->text().toStdString())), float(stof( ui->TxtLongitude_2->text().toStdString())));
        //emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_3->text().toStdString())), float(stof( ui->TxtLongitude_3->text().toStdString())));
        //emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_4->text().toStdString())), float(stof( ui->TxtLongitude_4->text().toStdString())));
        //emit new_balise(*balise);
    }


}
