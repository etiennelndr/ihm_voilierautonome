#include "meteo.h"


/**
 * CONSTRUCTOR
 *
 * @brief Meteo::Meteo : TODO
 * @param _id
 * @param lat
 * @param lon
 */
Meteo::Meteo(int _id, float lat, float lon) {
    id        = _id;
    vitesse   = -1.0f ;
    cap       = -1.0f ;
    longitude = -1.0f ;
    latitude  = -1.0f ;
}