#include "balise_IHM.h"
#include "ui_Balise_IHM.h"

Balise_IHM::Balise_IHM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Balise_IHM)
{
    ui->setupUi(this);
}

Balise_IHM::~Balise_IHM(){
    delete ui;
}

/*void Balise_IHM::AffichageBateaux()
{
    qDebug() << "hehe";
}*/

void Balise_IHM::on_BtnValider_clicked()
{
    if(!(ui->TxtLatitude_1->text().isEmpty() || ui->TxtLongitude_1->text().isEmpty() ||
         ui->TxtLatitude_2->text().isEmpty() || ui->TxtLongitude_2->text().isEmpty() ||
         ui->TxtLatitude_3->text().isEmpty() || ui->TxtLongitude_3->text().isEmpty() ||
         ui->TxtLatitude_4->text().isEmpty() || ui->TxtLongitude_4->text().isEmpty())){
        Balise* balise = new Balise(float(stof(ui->TxtLatitude_1->text().toStdString())), float(stof( ui->TxtLongitude_1->text().toStdString())));
        emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_2->text().toStdString())), float(stof( ui->TxtLongitude_2->text().toStdString())));
        emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_3->text().toStdString())), float(stof( ui->TxtLongitude_3->text().toStdString())));
        emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_4->text().toStdString())), float(stof( ui->TxtLongitude_4->text().toStdString())));
        emit new_balise(*balise);
        balise = new Balise(-1.0f,-1.0f);
        emit new_balise(*balise);
        this->close();
    }
    else{
        qDebug() << "Coucou";
    }


}
