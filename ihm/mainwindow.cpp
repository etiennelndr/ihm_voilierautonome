#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "mainwindow.h"
#include<QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QKeyEvent>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QRadioButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     barre=voile=10.0f; //Dansl'attente d'une initialisation par le serveur
     delta_barre=delta_voile=0.5f; // a modifier de façon empirique pour rester précis mais efficace dans les commandes du bateau
     connected=false;
}

MainWindow::~MainWindow()
{
     delete ui;
}

void MainWindow::on_RadioControle_clicked() {
    if(ui->RadioControle->isChecked()) {
        QMessageBox::information(this,"Informations autour du bateau","Utiliser les fleches du clavier pour contrôler le bateau");
    } else {

    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->RadioControle->isChecked()) {
        if(event->key()==Qt::Key_Up) {
            cout << "Key_up" << endl;
            voile+=delta_voile;
            client->set_voile(&voile);
        } else if (event->key()==Qt::Key_Down) {
            cout << "Key_down" << endl;
            voile-=delta_voile;
            client->set_voile(&voile);
        } else if (event->key()==Qt::Key_Right) {
            cout << "Key_right" << endl;
            barre += delta_barre;
            client->set_barre(&barre);
        } else if (event->key()==Qt::Key_Left) {
            cout << "Key_left" << endl;
            barre -= delta_barre;
            client->set_barre(&barre);
        }
    } else
      QMessageBox::information(this,"Error","Tu ne peux pas contrôler le bateau");
}

void MainWindow::on_BtnConxDeconx_clicked() {
    if(ui->BtnConxDeconx->text() ==  "Connexion") {
        client = new ClientTcp(QString("127.0.0.1"), 4000);
        connect(client, SIGNAL(connexion_status(bool)), this, SLOT(set_connexion(bool)));
    } else {
        ui->BtnConxDeconx->setText("Connexion");
    }
}

void MainWindow::set_connexion(bool status){
    connected = status;
    if(connected)
        ui->BtnConxDeconx->setText("Déconnexion");
    else
        ui->BtnConxDeconx->setText("Connexion");
}

void MainWindow::on_Btn_Exit_clicked() {
   close();
}
