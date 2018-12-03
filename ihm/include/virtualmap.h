#ifndef VIRTUALMAP_H
#define VIRTUALMAP_H

#include <QMainWindow>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <cmath>
#include "boat.h"
#include "balise.h"
#include <QtGui>
#include <QtCore>
#include <QPainter>


using namespace std;

class VirtualMap
{
public:
    VirtualMap(Balise* b1, Balise* b2, Balise* b3, Balise* b4);
    //getters
    float get_start_latitude() const        {return start_latitude;}
    float get_start_longitude() const       {return start_longitude;}
    float get_end_latitude() const          {return end_latitude;}
    float get_end_langitude() const         {return end_longitude;}
    //setters
    void  set_start_latitude(float lat)     {start_latitude = lat;}
    void  set_start_longitude(float lon)    {start_longitude = lon;}
    void  set_end_latitude(float lat)       {end_latitude = lat;}
    void  set_end_longitude(float lon)      {end_longitude = lon;}

    void display_boats(vector<Boat*> boats, QMainWindow* mw);



private :
    float start_latitude;
    float start_longitude;
    float end_latitude;
    float end_longitude;
    vector <Balise*> balises;
    QGraphicsScene* scene;
    QRectF* zone;
    QGraphicsView* vie;
    int scale_lat(float l);
    int scale_lon(float l);
    float angle(float l);
    void set_start_and_end_lat_and_long();

};



#endif // VIRTUALMAP_H
