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
#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

/**
 * CONSTRUCTOR
 *
 * @brief MainWindow::MainWindow : TODO
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent, int nb) : QMainWindow(parent), ui(new Ui::MainWindow) {
     ui->setupUi(this);
     ui->RadioControle->setCheckable(false);
     delta_barre=delta_voile=0.5f; // a modifier de façon empirique pour rester précis mais efficace dans les commandes du bateau
     connected=false;
     ui->label_2->hide();



     //QLabel *label_13 = new QLabel();

     /*QGraphicsScene *scene = new QGraphicsScene(this);
     QGraphicsProxyWidget *w = scene->addWidget(ui->label_13);
     w->setPos(50, 50);
     w->setRotation(45);
     ui->graphicsView->setScene(scene);*/
}


/**
 * DESTRUCTOR
 *
 * @brief MainWindow::~MainWindow : TODO
 */
MainWindow::~MainWindow() {
    qDeleteAll(boats);
    qDeleteAll(meteos);
    qDeleteAll(balises);
    delete virtual_map;
    delete station_IHM;
    delete balise_IHM;
    delete combobox12;
    delete line_5;
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
 * @brief MainWindow::paintEvent : TODO
 * @param event
 */
void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    if (virtual_map != nullptr){
        virtual_map->display_boats(boats, this);
    }
    display_Boussole();
    display_Gite_Tangage();
}

/**
 * METHOD
 *
 * @brief MainWindow::display_Boussole
 */
void MainWindow::display_Boussole(){
    QPainter ellipsePainter(this);

    QPen pen1(Qt::red);
    QPen pen2(Qt::black);
    QPen pointpen(Qt::red);

    pointpen.setWidth(10);

    QPen lignepen(Qt::black);
    pointpen.setWidth(4);

    pen1.setWidth(5);
    ellipsePainter.setPen(pen1);
    ellipsePainter.drawEllipse(QRect(830,94,75,75));

    ellipsePainter.setPen(pen2);
    ellipsePainter.drawText(863,87,"N");
    ellipsePainter.drawText(863,192,"S");
    ellipsePainter.drawText(914,139,"W");
    ellipsePainter.drawText(810,139,"E");
    //------ Rotate fleche

    /*QPixmap pixmap(*ui->fleche->pixmap());
    QMatrix rm;
    rm.rotate(0);
    pixmap = pixmap.transformed(rm);
    ui->fleche->setPixmap(pixmap);*/

    /*QPoint p1;
    p1.setX(850);
    p1.setY(150);

    QPoint p2;
    p2.setX(880);
    p2.setY(112);

    ellipsePainter.setPen(lignepen);
    ellipsePainter.drawLine(p1,p2);
    ellipsePainter.setPen(pointpen);
    ellipsePainter.drawPoint(p2);
    ellipsePainter.rotate(30);*/

    /*QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    QBrush greenBrush(Qt::white);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);


    // addEllipse(x,y,w,h,pen,brush)

    QGraphicsEllipseItem *ellipse;
    ellipse = scene->addEllipse(75, 75, 90, 85, outlinePen, greenBrush);
    QPushButton *lbl = new QPushButton();
    QGraphicsProxyWidget *w = scene->addWidget(lbl);
            w->setRotation(45);
            ui->graphicsView->setScene(scene);*/


}

/**
 * METHOD
 *
 * @brief MainWindow::display_Gite_Tangage : TODO
 */
void MainWindow::display_Gite_Tangage(){
    QPainter ellipsePainter(this);

    QPen pen1(Qt::red);
    QPen pen2(Qt::black);
    QPen pointpen(Qt::red);

    pointpen.setWidth(10);

    QPen lignepen(Qt::blue);
    pen1.setWidth(5);

    pen2.setWidth(5);
    ellipsePainter.setPen(pen2);

    //------------------------------------Gite
    ellipsePainter.drawEllipse(QRect(720,530,75,75));

    QPoint p1;
    p1.setX(722);
    p1.setY(565);

    QPoint p2;
    p2.setX(792);
    p2.setY(565);

    pointpen.setWidth(5);
    ellipsePainter.setPen(lignepen);
    ellipsePainter.drawLine(p1,p2);

    pointpen.setWidth(5);
    ellipsePainter.setPen(pointpen);

    //------------------------------------Tangage
    pen2.setWidth(5);
    ellipsePainter.setPen(pen2);
    ellipsePainter.drawEllipse(QRect(925,530,75,75));
    QPoint p3;
    p3.setX(926);
    p3.setY(565);

    QPoint p4;
    p4.setX(997);
    p4.setY(565);

    ellipsePainter.setPen(lignepen);
    ellipsePainter.drawLine(p3,p4);

    pointpen.setWidth(5);
    ellipsePainter.setPen(pointpen);
}

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

/**
 * METHOD
 *
 * @brief MainWindow::get_boat : return a bot thanks to an id
 * @param id
 * @return
 */
Boat* MainWindow::get_boat(int id){
    Boat* boat = nullptr;
    for (unsigned int i=0;i<boats.size();i++) {
        if(boats.at(i)->get_id()==id)
            boat = boats.at(i);
    }
    return boat;
}

/**
 * METHOD
 *
 * @brief MainWindow::get_meteo : return a weather station thanks to an id
 * @param id
 * @return
 */
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
void MainWindow::on_actionStations_triggered()
{
    station_IHM = new StationsMeteo(this);
    connect(station_IHM, SIGNAL(new_meteo(Meteo)), this, SLOT(add_meteo(Meteo)));
    station_IHM->show();
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

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::add_balise : add a new tag
 * @param b
 */
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

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::add_meteo : add a new weather station
 * @param m
 */
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
    }
}


/**
 * SLOT -> TODO
 *
 * @brief MainWindow::on_combo_activated : TODO
 * @param arg1
 */
void MainWindow::on_combo_activated(const QString &arg1)
{

}
