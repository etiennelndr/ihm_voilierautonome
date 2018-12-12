#include "meteo.h"


/**
 * CONSTRUCTOR
 *
 * @brief Meteo::Meteo : TODO
 * @param _id
 * @param lat
 * @param lon
 */
Meteo::Meteo(int _id, float lat=0.0f, float lon=0.0f) {
    id        = _id;
    vitesse   = 0.0f ;
    cap       = 0.0f ;
    longitude = lon ;
    latitude  = lat ;
}

Meteo::Meteo(bool _end_of_transfer){
    end_of_transfer = _end_of_transfer;
}
