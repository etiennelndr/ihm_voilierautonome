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
#include<QRadioButton>
#include<QTextBrowser>
#include<balise.h>
#include<balise_IHM.h>
#include <QDebug>
/**
 * CONSTRUCTOR
 *
 * @brief MainWindow::MainWindow : TODO
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent,int nb) : QMainWindow(parent), ui(new Ui::MainWindow) {
     ui->setupUi(this);
     ui->RadioControle->setCheckable(false);
     delta_barre=delta_voile=0.5f; // a modifier de façon empirique pour rester précis mais efficace dans les commandes du bateau
     connected=false;
     ui->label_2->hide();

     // Intervale du Tension de la voile
         ui->TensionVoile->setRange(1,100);
     // Intervale du Tension de la Barre
         ui->TensionBarre->setRange(1,100);
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
    if (virtual_map != nullptr){
        virtual_map->display_boats(boats, this);
    }

    display_Boussle(this);
    display_Gite_Tangage(this);


}

void MainWindow::display_Boussle(QMainWindow* mw){

    QPainter ellipsePainter(mw);
    // -------- affficher la cercle du boussle

    QPen pen1(Qt::red);
    pen1.setWidth(5);
    ellipsePainter.setPen(pen1);
    ellipsePainter.drawEllipse(QRect(830,94,75,75));


    // -------- affficher les directions du boussle

    QPen pen2(Qt::black);
    ellipsePainter.setPen(pen2);
    ellipsePainter.drawText(863,87,"N");
    ellipsePainter.drawText(863,192,"S");
    ellipsePainter.drawText(914,139,"W");
    ellipsePainter.drawText(810,139,"E");

    //------ Rotate la fleche du Boussle

    QPixmap pixmap(*ui->fleche->pixmap());
    QMatrix rm;

    rm.rotate(0);
    pixmap = pixmap.transformed(rm);
    ui->fleche->setPixmap(pixmap);
}
void MainWindow::Rotate_gite_tangage(Boat b){
    //----- Rotate Gite(Afficher l'angle d'inclinaison)
    QPixmap pixmap1(*ui->gite_lbl->pixmap());
    QMatrix rm1;
    rm1.rotate(b.get_gite());
    pixmap1 = pixmap1.transformed(rm1);
    ui->gite_lbl->setPixmap(pixmap1);

    //-------- Rotate tangage(Afficher l'angle d'inclinaison)
    QPixmap pixmap2(*ui->tangage_lb->pixmap());
    QMatrix rm2;
    rm2.rotate(b.get_tangage());
    pixmap2 = pixmap2.transformed(rm2);
    ui->tangage_lb->setPixmap(pixmap2);
}

void MainWindow::display_Gite_Tangage(QMainWindow* mw){
    QPainter ellipsePainter(mw);




    //--------Afficher la cercle du Gite

    QPen pen2(Qt::black);
    pen2.setWidth(5);
    ellipsePainter.setPen(pen2);
    ellipsePainter.drawEllipse(QRect(720,530,75,75));

    //-------Afficher le ligne bleu du l'eau
    QPen lignepen(Qt::blue);
    lignepen.setWidth(2);

    QPoint p1;
    p1.setX(722);
    p1.setY(565);

    QPoint p2;
    p2.setX(792);
    p2.setY(565);

    ellipsePainter.setPen(lignepen);
    ellipsePainter.drawLine(p1,p2);

    /*//----Rotate Gite(Afficher l'angle d'inclinaison)
    QPixmap pixmap1(*ui->gite_lbl->pixmap());
    QMatrix rm1;
    rm1.rotate(0);
    pixmap1 = pixmap1.transformed(rm1);
    ui->gite_lbl->setPixmap(pixmap1);*/



    //-------Afficher la cercle du Tangage
    pen2.setWidth(5);
    ellipsePainter.setPen(pen2);
    ellipsePainter.drawEllipse(QRect(925,530,75,75));


    //-------Afficher le ligne bleu du l'eau
    QPoint p3;
    p3.setX(926);
    p3.setY(565);

    QPoint p4;
    p4.setX(997);
    p4.setY(565);

    ellipsePainter.setPen(lignepen);
    ellipsePainter.drawLine(p3,p4);


    /*//----Rotate Tangage(Afficher  l'angle d'inclinaison)
    QPixmap pixmap2(*ui->tangage_lb->pixmap());
    QMatrix rm2;
    rm2.rotate(0);
    pixmap2 = pixmap2.transformed(rm2);
    ui->tangage_lb->setPixmap(pixmap2);*/

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
        if(meteos.at(i)->get_id()==id)
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

// Utitliser les fleches pour controller les bateaux
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(ui->RadioControle->isChecked() && connected)
    {
        if(event->key() == Qt::Key_Up) {
            cout << "Key_up" << endl;
            get_boat(my_id)->set_voile(get_boat(my_id)->get_voile()+delta_voile);
            client->set_voile(get_boat(my_id)->get_voile_addr());
            //GET VOILE GET BVARRE
            ui->TensionVoile->setValue(50);
        } else if (event->key() == Qt::Key_Down) {
            cout << "Key_down" << endl;
            get_boat(my_id)->set_voile(get_boat(my_id)->get_voile()-delta_voile);
            client->set_voile(get_boat(my_id)->get_voile_addr());            
            ui->TensionVoile->setValue(50);
        } else if (event->key() == Qt::Key_Right) {
            cout << "Key_right" << endl;
            get_boat(my_id)->set_barre(get_boat(my_id)->get_barre()+delta_barre);
            client->set_barre(get_boat(my_id)->get_barre_addr());        
            ui->TensionBarre->setValue(50);
        } else if (event->key() == Qt::Key_Left) {
            cout << "Key_left" << endl;
            get_boat(my_id)->set_barre(get_boat(my_id)->get_barre()-delta_barre);
            client->set_barre(get_boat(my_id)->get_barre_addr());
            ui->TensionBarre->setValue(50);
        }
    }else if (event->key()==Qt::Key_Up || event->key()==Qt::Key_Down || event->key()==Qt::Key_Left || event->key()==Qt::Key_Right)
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
        get_boat(id_concern)->set_longitude(l);
        update();
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

// Afficher le fenetre des stations meteos
void MainWindow::on_actionStations_triggered()
{
    station_IHM = new sationsmeteo(this);
    connect(station_IHM, SIGNAL(new_meteo(Meteo)), this, SLOT(add_meteo(Meteo)));
    station_IHM->show();
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::on_actionBalise_triggered : TODO
 */

// Afficher le fenetre des Balises
void MainWindow::on_actionBalise_triggered()
{
    balise_IHM = new Balise_IHM(this);
    connect(balise_IHM, SIGNAL(new_balise(Balise)), this, SLOT(add_balise(Balise)));
    balise_IHM->show();
}

void MainWindow::add_balise(Balise b){
    if(b.get_end_of_transfer()){ //Transfer of data is finished
        ui->actionBalise->setDisabled(true);
        virtual_map = new VirtualMap(balises.at(0), balises.at(1), balises.at(2), balises.at(3));
    }
    else {
        balises.push_back(new Balise(b.get_latitude(), b.get_longitude()));
        qDebug() << "new Balise added";
    }
}


void MainWindow::add_meteo(Meteo m){
    if(m.get_latitude()<0.0f){ //Transfer of data is finished
        ui->actionStations->setDisabled(true);
    }
    else{
        meteos.push_back(new Meteo(m.get_id(),m.get_latitude(), m.get_latitude()));
        ui->combobox12->addItem(QString::number(m.get_id()));
        qDebug() << "new Meteo added with id : " << m.get_id();

        QPixmap pixmap(*ui->fleche->pixmap());
        QMatrix rm;
        rm.rotate( m.get_id());
        pixmap = pixmap.transformed(rm);
        ui->fleche->setPixmap(pixmap);

        QPixmap pixmap1(*ui->gite_lbl->pixmap());
        QMatrix rm1;
        rm1.rotate( m.get_latitude());
        pixmap1 = pixmap1.transformed(rm1);
        ui->gite_lbl->setPixmap(pixmap1);

        QPixmap pixmap2(*ui->tangage_lb->pixmap());
        QMatrix rm2;
        rm2.rotate( m.get_latitude());
        pixmap2 = pixmap2.transformed(rm2);
        ui->tangage_lb->setPixmap(pixmap2);
    }
}



void MainWindow::on_combo_activated(const QString &arg1)
{

}
