#include "boat.h"

/**
 * CONSTRUCTOR
 *
 * @brief Boat::Boat
 * @param _id
 * @param _is_mine
 * @param r
 * @param g
 * @param b
 */
Boat::Boat(int _id, bool _is_mine, int r, int g, int b) {
    color     = new QColor(r, g, b);
    id        = _id;
    is_mine   = _is_mine;
    vitesse   = 0.0f ;
    cap       = 0.0f ;
//    longitude = 0.0f ;
//    latitude  = 0.0f ;
    longitude = -4.613100f ;
    latitude  = 48.430300f ;
    gite      = 0.0f ;
    tangage   = 0.0f ;
    barre     = 0.0f ;
    voile     = 0.0f ;
}
