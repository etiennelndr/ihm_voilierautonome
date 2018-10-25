#include "boat.h"

Boat::Boat(int _id, bool _is_mine, int r, int g, int b)
{
    color = new QColor(r, g, b);
    id = _id;
    is_mine = _is_mine;
    vitesse = -1.0f ;
    cap = -1.0f ;
    longitude = -1.0f ;
    latitude = -1.0f ;
    gite = -1.0f ;
    tangage = -1.0f ;
    barre = -1.0f ;
    voile = -1.0f ;
}
