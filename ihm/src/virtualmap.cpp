#include "virtualmap.h"
#include <QDebug>

VirtualMap::VirtualMap(){
    std::cout<<"Nothing";
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
        if (boat->get_latitude()>0.0f && boat->get_longitude()>0.0f){
            ellipsePainter.fillRect(scale_lat(boat->get_latitude()),scale_lon(boat->get_longitude()),20,75,boat->get_color());
            qDebug() <<boat->get_latitude();
        }
        else {
             ellipsePainter.fillRect(boats.size()*(245-(30/2))+30*i,423,20,75,boat->get_color());
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


    QRectF rectangle(60, 210, 350, 500);

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
//int VirtualMap::get_xy(float lat,float lng)
//{
//int mapWidth=2058;
//int mapHeight=1746;
//float factor=.404;
//int x_adj=-391;
//int y_adj=37;
//float x = (mapWidth*(180+lng)/360)%mapWidth+(mapWidth/2);
//float latRad = lat*Math.PI/180;
//float mercN = Math.log(Math.tan((Math.PI/4)+(latRad/2)));
//float y = (mapHeight/2)-(mapWidth*mercN/(2*Math.PI));
//return { x: x*factor+x_adj,y: y*factor+y_adj}
//}

int VirtualMap::scale_lat(float l){
    start_latitude = 300;
    end_latitude = 500;
    float pos = l-start_latitude;
    pos = pos*(end_latitude-start_latitude);
    qDebug() << pos;
    return int(pos);
}
int VirtualMap::scale_lon(float l){
    start_longitude = 300;
    end_longitude = 500;
    float pos = l-start_longitude;
    pos = pos*(end_longitude-start_longitude);
    return int(pos);
}
float VirtualMap::angle(float l) {
    return float((qrand()%360));
}
