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

/**
 * CONSTRUCTOR
 *
 * @brief MainWindow::MainWindow : TODO
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
     boats.push_back(new Boat(1,true, 255,0,0));
     ui->setupUi(this);
     ui->RadioControle->setCheckable(false);
     delta_barre=delta_voile=0.5f; // a modifier de façon empirique pour rester précis mais efficace dans les commandes du bateau
     connected=false;
     ui->label_2->hide();
}

/**
 * DESTRUCTOR
 *
 * @brief MainWindow::~MainWindow : TODO
 */
MainWindow::~MainWindow() {
     delete ui;
}

/*--------------------------*
 *                          *
 *         METHODS          *
 *                          *
 *--------------------------*/
/**
 * METHOD
 *
 * @brief MainWindow::create_connections : TODO
 */
void MainWindow::create_connections(){
    connect(client, SIGNAL(connexion_status(bool)), this, SLOT(set_connexion(bool)));
    connect(client, SIGNAL(send_longitude(float, int)), this, SLOT(receive_longitude(float, int)));
    connect(client, SIGNAL(send_latitude(float, int)), this, SLOT(receive_latitude(float, int)));
    connect(client, SIGNAL(send_cap(float, int)), this, SLOT(receive_cap(float, int)));
    connect(client, SIGNAL(send_vitesse(float, int)), this, SLOT(receive_vitesse(float, int)));
    connect(client, SIGNAL(send_gite(float, int)), this, SLOT(receive_gite(float, int)));
    connect(client, SIGNAL(send_tangage(float, int)), this, SLOT(receive_tangage(float, int)));
    connect(client, SIGNAL(send_barre(float, int)), this, SLOT(receive_barre(float, int)));
    connect(client, SIGNAL(send_voile(float, int)), this, SLOT(receive_voile(float, int)));
}

/**
 * METHOD
 *
 * @brief MainWindow::keyPressEvent : TODO
 * @param event
 */
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(ui->RadioControle->isChecked() && connected) {
        if(event->key() == Qt::Key_Up) {
            cout << "Key_up" << endl;
            boats.at(0)->set_voile(boats.at(0)->get_voile()+delta_voile);
            client->set_voile(boats.at(0)->get_voile_addr());
        } else if (event->key() == Qt::Key_Down) {
            cout << "Key_down" << endl;
            boats.at(0)->set_voile(boats.at(0)->get_voile()-delta_voile);
            client->set_voile(boats.at(0)->get_voile_addr());
        } else if (event->key() == Qt::Key_Right) {
            cout << "Key_right" << endl;
            boats.at(0)->set_barre(boats.at(0)->get_barre()+delta_barre);
            client->set_barre(boats.at(0)->get_barre_addr());
        } else if (event->key() == Qt::Key_Left) {
            cout << "Key_left" << endl;
            boats.at(0)->set_barre(boats.at(0)->get_barre()-delta_barre);
            client->set_barre(boats.at(0)->get_barre_addr());
        }
    } else if (event->key()==Qt::Key_Up || event->key()==Qt::Key_Down || event->key()==Qt::Key_Left || event->key()==Qt::Key_Right)
      QMessageBox::information(this,"Error","Tu ne peux pas contrôler le bateau");
}

/*--------------------------*
 *                          *
 *          SLOTS           *
 *                          *
 *--------------------------*/
/**
 * SLOT -> TODO
 *
 * @brief MainWindow::on_RadioControle_clicked : TODO
 */
void MainWindow::on_RadioControle_clicked() {
    if(ui->RadioControle->isChecked()) {
        QMessageBox::information(this,"Informations autour du bateau","Utiliser les fleches du clavier pour contrôler le bateau");
    } else {

    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::on_BtnConxDeconx_clicked : TODO
 */
void MainWindow::on_BtnConxDeconx_clicked() {
    if(ui->BtnConxDeconx->text() ==  "Connexion" && ui->spinBox->value()>0) {
        client = new ClientTcp(QString("127.0.0.1"), 4000, ui->spinBox->value());
        ui->label_2->show();
        ui->label_2->setText("Votre id: " + QString::number(ui->spinBox->value()));
        ui->spinBox->close();
        ui->label->close();
        create_connections();
    } else {
        ui->BtnConxDeconx->setText("Connexion");
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::set_connexion : TODO
 * @param status
 */
void MainWindow::set_connexion(bool status){
    connected = status;
    if(connected) {
        ui->BtnConxDeconx->setText("Déconnexion");
        ui->RadioControle->setCheckable(true);
    } else {
        ui->BtnConxDeconx->setText("Connexion");
        ui->RadioControle->setCheckable(false);
        QMessageBox::information(this,"Error","Vous n'êtes pas/plus connecté au serveur !");
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::on_Btn_Exit_clicked : TODO
 */
void MainWindow::on_Btn_Exit_clicked() {
   close();
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_longitude : TODO
 * @param l
 * @param id_concern
 */
void MainWindow::receive_longitude(float l, int id_concern){
    cout << "New longitude of " << id_concern << " : " << l <<endl;
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_latitude : TODO
 * @param l
 * @param id_concern
 */
void MainWindow::receive_latitude(float l, int id_concern){
    cout << "New latitude of " << id_concern << " : " << l <<endl;
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_cap : TODO
 * @param c
 * @param id_concern
 */
void MainWindow::receive_cap(float c, int id_concern){
    cout << "New cap of " << id_concern << " : " << c <<endl;
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_vitesse : TODO
 * @param v
 * @param id_concern
 */
void MainWindow::receive_vitesse(float v, int id_concern){
    cout << "New speed of " << id_concern << " : " << v <<endl;
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_gite : TODO
 * @param g
 * @param id_concern
 */
void MainWindow::receive_gite(float g, int id_concern){
    cout << "New gite of " << id_concern << " : " << g <<endl;
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_tangage : TODO
 * @param t
 * @param id_concern
 */
void MainWindow::receive_tangage(float t, int id_concern){
    cout << "New tangage of " << id_concern << " : " << t <<endl;
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_barre : TODO
 * @param b
 * @param id_concern
 */
void MainWindow::receive_barre(float b, int id_concern){
    cout << "New barre of " << id_concern << " : " << b <<endl;
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_voile : TODO
 * @param v
 * @param id_concern
 */
void MainWindow::receive_voile(float v, int id_concern){
    cout << "New voile of " << id_concern << " : " << v <<endl;
}
