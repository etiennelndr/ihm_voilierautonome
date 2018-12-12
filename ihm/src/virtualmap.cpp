#include "virtualmap.h"
#include <QDebug>

/**
 * CONSTRUCTOR
 *
 * @brief VirtualMap::VirtualMap : TODO
 * @param b1
 * @param b2
 * @param b3
 * @param b4
 */
VirtualMap::VirtualMap(Balise* b1, Balise* b2, Balise* b3, Balise* b4){
    balises.push_back(b1);
    balises.push_back(b2);
    balises.push_back(b3);
    balises.push_back(b4);

    //Define the start and end of longitude and latitude of the displayed window
    set_start_and_end_lat_and_long();

}

/**
 * DESTRUCTOR
 * @brief VirtualMap::~VirtualMap : TODO
 */
VirtualMap::~VirtualMap() {
    qDeleteAll(balises);
    delete scene;
    delete zone;
    delete vie;
}

void VirtualMap::set_start_and_end_lat_and_long(){
    //Initialisation with balises.at(0)
    start_latitude=balises.at(0)->get_latitude();
    end_latitude=balises.at(0)->get_latitude();
    //Checking balises.at(1)
    if (start_latitude  >  balises.at(1)->get_latitude())  {start_latitude=balises.at(1)->get_latitude();}
    if (end_latitude    <  balises.at(1)->get_latitude())  {end_latitude=balises.at(1)->get_latitude();}
    //Checking balises.at(2)
    if (start_latitude  >  balises.at(2)->get_latitude())  {start_latitude=balises.at(2)->get_latitude();}
    if (end_latitude    <  balises.at(2)->get_latitude())  {end_latitude=balises.at(2)->get_latitude();}
    //Checking balises.at(3)
    if (start_latitude  >  balises.at(3)->get_latitude())  {start_latitude=balises.at(3)->get_latitude();}
    if (end_latitude    <  balises.at(3)->get_latitude())  {end_latitude=balises.at(3)->get_latitude();}

    //Initialisation with balises.at(0)
    start_longitude=balises.at(0)->get_longitude();
    end_longitude=balises.at(0)->get_longitude();
    //Checking balises.at(1)
    if (start_longitude >  balises.at(1)->get_longitude()) {start_longitude=balises.at(1)->get_longitude();}
    if (end_longitude   <  balises.at(1)->get_longitude()) {end_longitude=balises.at(1)->get_longitude();}
    //Checking balises.at(2)
    if (start_longitude >  balises.at(2)->get_longitude()) {start_longitude=balises.at(2)->get_longitude();}
    if (end_longitude   <  balises.at(2)->get_longitude()) {end_longitude=balises.at(2)->get_longitude();}
    //Checking balises.at(3)
    if (start_longitude >  balises.at(3)->get_longitude()) {start_longitude=balises.at(3)->get_longitude();}
    if (end_longitude   <  balises.at(3)->get_longitude()) {end_longitude=balises.at(3)->get_longitude();}

    float offset = max(0.3f*fabs((end_latitude-start_latitude)), 0.3f*fabs((end_longitude-start_longitude)));
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

        //qDebug() << "id : "<< boat->get_id() << " / longitude : " << boat->get_longitude() << " / latitude :" << boat->get_latitude();
        if (start_latitude<boat->get_latitude() && boat->get_latitude()<end_latitude && start_longitude<boat->get_longitude() && boat->get_longitude()<end_longitude){
            ellipsePainter.fillRect(scale_lon(boat->get_longitude())-5,scale_lat(boat->get_latitude())-15,10,30,boat->get_color());
            qDebug() <<boat->get_latitude();
        }
        else {
            if (!(start_latitude<boat->get_latitude()))
                qDebug() << "start_latitude : " << boat->get_latitude() << " < " << start_latitude;
            if (!(boat->get_latitude()<end_latitude))
                qDebug() << "end_latitude : " << boat->get_latitude() << " > " << end_latitude;
            if (!(start_longitude<boat->get_longitude()))
                qDebug() << "start_longitude : " << boat->get_longitude() << "<" << start_longitude;
            if (!(boat->get_longitude()<end_longitude))
                qDebug() << "end_longitude : " << boat->get_longitude() << ">" << end_longitude;
            ellipsePainter.fillRect(20*i+(310-boats.size()*10),460,10,30,boat->get_color());
        }
        ellipsePainter.fillRect(310-(boats.size()*5)+30*i,720,10,10,boat->get_color());
        ellipsePainter.drawText(310-(boats.size()*5)+30*i,745,QString::number(boat->get_id()));
    }

    pen2.setWidth(8);

    //Affichage des balises
    ellipsePainter.setPen(pen2);
    ellipsePainter.drawEllipse(QRect(scale_lon(balises.at(0)->get_longitude())-10,scale_lat(balises.at(0)->get_latitude())-10,20,20));
    ellipsePainter.drawEllipse(QRect(scale_lon(balises.at(1)->get_longitude())-10,scale_lat(balises.at(1)->get_latitude())-10,20,20));
    ellipsePainter.drawEllipse(QRect(scale_lon(balises.at(2)->get_longitude())-10,scale_lat(balises.at(2)->get_latitude())-10,20,20));
    ellipsePainter.drawEllipse(QRect(scale_lon(balises.at(3)->get_longitude())-10,scale_lat(balises.at(3)->get_latitude())-10,20,20));


    QRectF rectangle(60, 210, 500, 500);

    QPainter painter(mw);
    painter.drawRect(rectangle);
}
int VirtualMap::scale_lat(float real_lat){
    float scaled_lat = (real_lat-start_latitude)*(500/(max(fabs(end_latitude-start_latitude),fabs(end_longitude-start_longitude))));
//    float scaled_lat = 10000*(real_lat-start_latitude)*(500/(10000*max(fabs(end_latitude-start_latitude),fabs(end_longitude-start_longitude))));
    return int(scaled_lat)+210; // offset de l'affichage du carre
}
int VirtualMap::scale_lon(float real_long){
    float scaled_long = (real_long-start_longitude)*(500/(max(fabs(end_latitude-start_latitude),fabs(end_longitude-start_longitude))));
//    float scaled_long = 10000*(real_long-start_longitude)*(500/10000*(max(fabs(end_latitude-start_latitude),fabs(end_longitude-start_longitude))));
    return int(scaled_long)+60;  // offset de l'affichage du carre
}
float VirtualMap::angle(float l) {
    return float((qrand()%360));
}
