#include "virtualmap.h"
#include "balise_IHM.h"
#include "ui_Balise_IHM.h"

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


    qDebug() << start_latitude << " / " << end_latitude << " / " << start_longitude << " / " << end_longitude;
}

void VirtualMap::display_boats(vector<Boat*> boats,QMainWindow* mw){
    QPainter ellipsePainter(mw);

    QPen pen1(Qt::black);
    QPen pen2(Qt::red);

    pen1.setWidth(8);
    ellipsePainter.setPen(pen1);


    for (unsigned int i = 0; i < boats.size(); i++) {

        Boat* boat = boats.at(i);
        if (boat->get_latitude()>0.0f && boat->get_longitude()>0.0f){
            ellipsePainter.fillRect(scale_lat(boat->get_latitude()),scale_lon(boat->get_longitude()),20,75,boat->get_color());
        }
        else {
             ellipsePainter.fillRect(245-(boats.size()*30/2)+30*i,423,20,75,boat->get_color());
        }
        ellipsePainter.fillRect(245-(boats.size()*30/2)+30*i,720,10,10,boat->get_color());
        ellipsePainter.drawText(245-(boats.size()*30/2)+30*i,745,QString::number(boat->get_id()));
    }

//    ellipsePainter.fillRect(114,292,20,75,Qt::green);
//    ellipsePainter.drawEllipse(QRect(100,280,50,100));

//    ellipsePainter.fillRect(300,450,20,75,Qt::blue);
//    ellipsePainter.drawEllipse(QRect(286,436,50,100));
    pen2.setWidth(8);

    ellipsePainter.setPen(pen2);
    ellipsePainter.drawEllipse(QRect(90,230,30,30));
    ellipsePainter.drawEllipse(QRect(350,230,30,30));
    ellipsePainter.drawEllipse(QRect(350,650,30,30));
    ellipsePainter.drawEllipse(QRect(90,650,30,30));


    QRectF rectangle(60, 210, 500, 500);

    QPainter painter(mw);
    painter.drawRect(rectangle);
}

int VirtualMap::scale_lat(float l){
    float pos = l-start_latitude;
    pos = pos*(end_latitude-start_latitude);
    return int(pos);
}
int VirtualMap::scale_lon(float l){
    float pos = l-start_longitude;
    pos = pos*(end_longitude-start_longitude);
    return int(pos);
}
float VirtualMap::angle(float l) {
    return float((qrand()%360));
}
