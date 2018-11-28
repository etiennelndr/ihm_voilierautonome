#include "virtualmap.h"
#include <QDebug>

VirtualMap::VirtualMap(Balise* b1, Balise* b2, Balise* b3, Balise* b4){
    balises.push_back(b1);
    balises.push_back(b2);
    balises.push_back(b3);
    balises.push_back(b4);


    //Define the start and end of longitude and latitude of the displayed window
    //Initialisation with b1
    start_latitude=b1->get_latitude();
    end_latitude=b1->get_latitude();
    start_longitude=b1->get_longitude();
    end_longitude=b1->get_longitude();
    //Checking b2
    if (start_latitude  >  b2->get_latitude())  {start_latitude=b2->get_latitude();}
    if (end_latitude    <  b2->get_latitude())  {end_latitude=b2->get_latitude();}
    if (start_longitude >  b2->get_longitude()) {start_longitude=b2->get_longitude();}
    if (end_longitude   <  b2->get_longitude()) {end_longitude=b2->get_longitude();}
    //Checking b3
    if (start_latitude  >  b3->get_latitude())  {start_latitude=b3->get_latitude();}
    if (end_latitude    <  b3->get_latitude())  {end_latitude=b3->get_latitude();}
    if (start_longitude >  b3->get_longitude()) {start_longitude=b3->get_longitude();}
    if (end_longitude   <  b3->get_longitude()) {end_longitude=b3->get_longitude();}
    //Checking b4
    if (start_latitude  >  b4->get_latitude())  {start_latitude=b4->get_latitude();}
    if (end_latitude    <  b4->get_latitude())  {end_latitude=b4->get_latitude();}
    if (start_longitude >  b4->get_longitude()) {start_longitude=b4->get_longitude();}
    if (end_longitude   <  b4->get_longitude()) {end_longitude=b4->get_longitude();}

    float offset = max(0.3f*(end_latitude-start_latitude), 0.3f*(end_longitude-start_longitude));
    start_latitude-=offset;
    end_latitude+=offset;
    start_longitude-=offset;
    end_longitude+=offset;
    qDebug() << start_latitude << " / " << end_latitude << " / " << start_longitude << " / " << end_longitude;
}

void VirtualMap::display_boats(vector<Boat*> boats,QMainWindow* mw){
    QPainter ellipsePainter(mw);

    QPen pen1(Qt::black);
    QPen pen2(Qt::red);
    QPen pen3(Qt::red);

    pen1.setWidth(8);
    ellipsePainter.setPen(pen1);


    for (unsigned int i = 0; i < boats.size(); i++) {

        Boat* boat = boats.at(i);

        qDebug() << "id : "<< boat->get_id() << " / longitude : " << boat->get_longitude() << " / latitude :" << boat->get_latitude();
        if (start_latitude<boat->get_latitude()<end_latitude && start_longitude<boat->get_longitude()<end_longitude){
            ellipsePainter.fillRect(scale_lat(boat->get_latitude()),scale_lon(boat->get_longitude()),10,30,boat->get_color());
            qDebug() <<boat->get_latitude();
        }
        else {
             ellipsePainter.fillRect(boats.size()*(270-(10/2))+30*i,460,10,30,boat->get_color());
        }
        ellipsePainter.fillRect(245-(boats.size()*30/2)+30*i,720,10,10,boat->get_color());
        ellipsePainter.drawText(245-(boats.size()*30/2)+30*i,745,QString::number(boat->get_id()));
    }

    pen2.setWidth(8);

    //Affichage des balises
    ellipsePainter.setPen(pen2);
    ellipsePainter.drawEllipse(QRect(scale_lat(balises.at(0)->get_latitude())-10,scale_lon(balises.at(0)->get_longitude())-10,20,20));
    ellipsePainter.drawEllipse(QRect(scale_lat(balises.at(1)->get_latitude())-10,scale_lon(balises.at(1)->get_longitude())-10,20,20));
    ellipsePainter.drawEllipse(QRect(scale_lat(balises.at(2)->get_latitude())-10,scale_lon(balises.at(2)->get_longitude())-10,20,20));
    ellipsePainter.drawEllipse(QRect(scale_lat(balises.at(3)->get_latitude())-10,scale_lon(balises.at(3)->get_longitude())-10,20,20));


    QRectF rectangle(60, 210, 500, 500);

    QPainter painter(mw);
    painter.drawRect(rectangle);

    //Vitesse de vente Vent
    ellipsePainter.setPen(pen3);
    pen3.setWidth(16);
    ellipsePainter.drawEllipse(QRect(670,90,75,75));
    ellipsePainter.drawText(700,80,"N");
    ellipsePainter.drawText(700,190,"S");
    ellipsePainter.drawText(650,135,"W");
    ellipsePainter.drawText(755,135,"E");


}
int VirtualMap::scale_lat(float real_lat){
    float scaled_lat = (real_lat-start_latitude)*(500/(max(end_latitude-start_latitude,end_longitude-start_longitude)));
    return int(scaled_lat)+60; // offset de l'affichage du carre
}
int VirtualMap::scale_lon(float real_long){
    float scaled_long = (real_long-start_longitude)*(500/(max(end_latitude-start_latitude,end_longitude-start_longitude)));
    return int(scaled_long)+210;  // offset de l'affichage du carre
}
float VirtualMap::angle(float l) {
    return float((qrand()%360));
}
