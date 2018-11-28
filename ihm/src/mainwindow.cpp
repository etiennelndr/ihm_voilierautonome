#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "balise_IHM.h"
#include "sationsmeteo.h"
#include <QPushButton>
#include "mainwindow.h"
#include<QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QKeyEvent>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QRadioButton>
#include<QTextBrowser>
#include<balise.h>
#include<balise_IHM.h>

/**
 * CONSTRUCTOR
 *
 * @brief MainWindow::MainWindow : TODO
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
     ui->setupUi(this);
     ui->RadioControle->setCheckable(false);
     delta_barre=delta_voile=0.5f; // a modifier de façon empirique pour rester précis mais efficace dans les commandes du bateau
     connected=false;
     ui->label_2->hide();
     virtual_map = new VirtualMap();
}

/**
 * DESTRUCTOR
 *
 * @brief MainWindow::~MainWindow : TODO
 */
MainWindow::~MainWindow() {
     delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    virtual_map->display_boats(boats, this);
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
    connect(client, SIGNAL(add_new_boat(int)), this, SLOT(add_new_boat(int)));
}

Boat* MainWindow::get_boat(int id){
    Boat* boat = nullptr;
    for (unsigned int i=0;i<boats.size();i++) {
        if(boats.at(i)->get_id()==id)
            boat = boats.at(i);
    }
    return boat;
}

Meteo* MainWindow::get_meteo(int id){
    Meteo* meteo = nullptr;
    for (unsigned int i=0;i<meteos.size();i++) {
        if(boats.at(i)->get_id()==id)
            meteo = meteos.at(i);
    }
    return meteo;
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
            get_boat(my_id)->set_voile(get_boat(my_id)->get_voile()+delta_voile);
            client->set_voile(get_boat(my_id)->get_voile_addr());
        } else if (event->key() == Qt::Key_Down) {
            cout << "Key_down" << endl;
            get_boat(my_id)->set_voile(get_boat(my_id)->get_voile()-delta_voile);
            client->set_voile(get_boat(my_id)->get_voile_addr());
        } else if (event->key() == Qt::Key_Right) {
            cout << "Key_right" << endl;
            get_boat(my_id)->set_barre(get_boat(my_id)->get_barre()+delta_barre);
            client->set_barre(get_boat(my_id)->get_barre_addr());
        } else if (event->key() == Qt::Key_Left) {
            cout << "Key_left" << endl;
            get_boat(my_id)->set_barre(get_boat(my_id)->get_barre()-delta_barre);
            client->set_barre(get_boat(my_id)->get_barre_addr());
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
        if(my_id != ui->spinBox->value()){
            my_id = ui->spinBox->value();
            boats.push_back(new Boat(ui->spinBox->value(),true, 90,115,210));
            this->update();
            ui->spinBox->close();
            ui->label->close();
            ui->label_2->show();
            ui->label_2->setText("Votre id: " + QString::number(my_id));
        }
        client = new ClientTcp(QString("127.0.0.1"), 4000, my_id);
//        if(get_boat(ui->spinBox->value())==NULL){
//            boats.push_back(new Boat(ui->spinBox->value(),true, 90,115,210));
//            ui->spinBox->close();
//            ui->label->close();
//        }
        create_connections();
    } else {
        cout << "on_BtnConxDeconx_clicked" << endl;
        // Delete the client
        if (client != nullptr) {
            delete client;
        }
        // Set it to nullptr
        client = nullptr;
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
    if(id_concern>0){
        MainWindow::get_boat(id_concern)->set_longitude(l);
        MainWindow::update();
        cout << "New longitude of " << id_concern << " : " << l <<endl;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_latitude : TODO
 * @param l
 * @param id_concern
 */
void MainWindow::receive_latitude(float l, int id_concern){
    if(id_concern>0){
        MainWindow::get_boat(id_concern)->set_latitude(l);
        MainWindow::update();
        cout << "New latitude of " << id_concern << " : " << l <<endl;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_cap : TODO
 * @param c
 * @param id_concern
 */
void MainWindow::receive_cap(float c, int id_concern){
    if(id_concern>0){
        get_boat(id_concern)->set_cap(c);
        update();
    } else if (id_concern<0) {
        get_meteo(id_concern)->set_cap(c);
        update();
    }
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
    if(id_concern>0){
        get_boat(id_concern)->set_vitesse(v);
        update();
    } else if (id_concern<0) {
        get_meteo(id_concern)->set_vitesse(v);
        update();
    }

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
    if(id_concern>0){
        MainWindow::get_boat(id_concern)->set_gite(g);
        MainWindow::update();
        cout << "New gite of " << id_concern << " : " << g <<endl;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_tangage : TODO
 * @param t
 * @param id_concern
 */
void MainWindow::receive_tangage(float t, int id_concern){
    if(id_concern>0){
        MainWindow::get_boat(id_concern)->set_tangage(t);
        MainWindow::update();
        cout << "New tangage of " << id_concern << " : " << t <<endl;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_barre : TODO
 * @param b
 * @param id_concern
 */
void MainWindow::receive_barre(float b, int id_concern){
    if(id_concern>0){
        MainWindow::get_boat(id_concern)->set_barre(b);
        MainWindow::update();
        cout << "New barre of " << id_concern << " : " << b <<endl;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::receive_voile : TODO
 * @param v
 * @param id_concern
 */
void MainWindow::receive_voile(float v, int id_concern){
    if(id_concern>0){
        MainWindow::get_boat(id_concern)->set_voile(v);
        MainWindow::update();
        cout << "New voile of " << id_concern << " : " << v <<endl;
    }
}


/**
 * SLOT -> TODO
 *
 * @brief MainWindow::add_new_boat_or_meteo : TODO
 * @param v
 * @param id_concern
 */
void MainWindow::add_new_boat(int id_concern){
    if(id_concern>0){
        boats.push_back(new Boat(id_concern,false, qrand()%255,qrand()%255,qrand()%255));
        MainWindow::update();
        cout << "New boat with id " << id_concern <<endl;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::on_actionStations_triggered : TODO
 */
void MainWindow::on_actionStations_triggered()
{
    // SationsMeteo statio;
    // statio.setModal(true);
     //statio.exec();
    station = new sationsmeteo(this);
    station->show();
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::on_actionBalise_triggered : TODO
 */
void MainWindow::on_actionBalise_triggered()
{
    balise_IHM = new Balise_IHM(this);
    connect(balise_IHM, SIGNAL(new_balise(Balise)), this, SLOT(add_balise(Balise)));
    balise_IHM->show();
}

void MainWindow::add_balise(Balise b){
    balises.push_back(&b);
    qDebug() << "new Balise added";
}
