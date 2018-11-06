#ifndef VIRTUALMAP_H
#define VIRTUALMAP_H

#include <QMainWindow>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "boat.h"
#include <iostream>


using namespace std;

class VirtualMap
{
public:
    VirtualMap();
    //getters
    float get_start_latitude() const        {return start_latitude;}
    float get_start_longitude() const       {return start_longitude;}
    float get_end_latitude() const          {return end_latitude;}
    float get_end_langitude() const         {return end_longitude;}
    float get_zoom() const                  {return zoom;}
    //setters
    void  set_start_latitude(float lat)     {start_latitude = lat;}
    void  set_start_longitude(float lon)    {start_longitude = lon;}
    void  set_end_latitude(float lat)       {end_latitude = lat;}
    void  set_end_longitude(float lon)      {end_longitude = lon;}
    void set_zoom(float z)                  {zoom = z;}

    void display_boats(vector<Boat*> boats, QMainWindow* mw);

private :
    float start_latitude;
    float start_longitude;
    float end_latitude;
    float end_longitude;
    float zoom;
    int scale(float l);
    QGraphicsScene* scene;
    QRectF* zone;
    QGraphicsView* view;

};

#endif // VIRTUALMAP_H
