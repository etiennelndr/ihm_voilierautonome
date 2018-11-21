#include "virtualmap.h"

VirtualMap::VirtualMap(){
    std::cout<<"Nothing";
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


    QRectF rectangle(60, 210, 350, 500);

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
