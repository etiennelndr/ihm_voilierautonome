#include "balise.h"

Balise::Balise(float _latitude, float _longitude){
    latitude = _latitude;
    longitude = _longitude;
}

Balise::Balise(bool _end_of_transfer){
    end_of_transfer = _end_of_transfer;
}
