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
    vitesse   = -1.0f ;
    cap       = -1.0f ;
    longitude = 12653.0f ;
    latitude  = 45232.0f ;
    gite      = -1.0f ;
    tangage   = -1.0f ;
    barre     = -1.0f ;
    voile     = -1.0f ;
}
