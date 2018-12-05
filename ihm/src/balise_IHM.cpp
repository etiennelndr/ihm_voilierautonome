#include "balise_IHM.h"
#include "ui_Balise_IHM.h"

Balise_IHM::Balise_IHM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Balise_IHM)
{
    ui->setupUi(this);
    //To reduce the time of simulation -- To be removed
    ui->TxtLatitude_1->setText("48.4302");
    ui->TxtLatitude_2->setText("48.4314");
    ui->TxtLatitude_3->setText("48.4300");
    ui->TxtLatitude_4->setText("48.4315");
    ui->TxtLongitude_1->setText("-4.6136");
    ui->TxtLongitude_2->setText("-4.6135");
    ui->TxtLongitude_3->setText("-4.6128");
    ui->TxtLongitude_4->setText("-4.6130");
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
        Balise* balise = new Balise(float(stof(ui->TxtLatitude_1->text().toStdString())), float(stof(ui->TxtLongitude_1->text().toStdString())));
        emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_2->text().toStdString())), float(stof(ui->TxtLongitude_2->text().toStdString())));
        emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_3->text().toStdString())), float(stof(ui->TxtLongitude_3->text().toStdString())));
        emit new_balise(*balise);
        balise = new Balise(float(stof(ui->TxtLatitude_4->text().toStdString())), float(stof(ui->TxtLongitude_4->text().toStdString())));
        emit new_balise(*balise);
        balise = new Balise(true);
        emit new_balise(*balise);
        this->close();
    }
    else{
        qDebug() << "Coucou";
    }


}
