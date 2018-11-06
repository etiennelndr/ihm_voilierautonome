#include "virtualmap.h"

VirtualMap::VirtualMap(){

}

void VirtualMap::display_boats(vector<Boat*> boats,QMainWindow* mw){
    QPainter ellipsePainter(mw);

    QPen pen1(Qt::black);
    QPen pen2(Qt::red);

    pen1.setWidth(8);
    ellipsePainter.setPen(pen1);


    for (unsigned int i = 0; i < boats.size(); i++) {
        Boat* boat = boats.at(i);
        ellipsePainter.fillRect(scale(boat->get_longitude())+14,scale(boat->get_latitude())+12,20,75,boat->get_color());
        ellipsePainter.drawEllipse(QRect(scale(boat->get_longitude()),scale(boat->get_latitude()),50,100));
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

int VirtualMap::scale(float l){
    return 215;
}
