#include "meteo.h"


/**
 * CONSTRUCTOR
 *
 * @brief Meteo::Meteo : TODO
 * @param _id
 * @param lat
 * @param lon
 */
Meteo::Meteo(int _id, float lat=-1.0f, float lon=-1.0f) {
    id        = _id;
    vitesse   = -1.0f;
    cap       = -1.0f;
    longitude = lon;
    latitude  = lat;
}
