#ifndef METEO_H
#define METEO_H

#endif // METEO_H

/**
 * @brief The Meteo class
 */
class Meteo {
public:
    Meteo(int id, float lat, float lon);

    //getters
    float  get_vitesse()        {return vitesse;}
    float  get_cap()            {return cap;}
    float  get_longitude()      {return longitude;}
    float  get_latitude()       {return latitude;}
    float* get_vitesse_addr()   {return &vitesse;}
    float* get_cap_addr()       {return &cap;}
    float* get_longitude_addr() {return &longitude;}
    float* get_latitude_addr()  {return &latitude;}

    //setters
    void set_vitesse(float _vitesse)    {vitesse=_vitesse;}
    void set_cap(float _cap)            {cap=_cap;}
    void set_longitude(float _longitude){longitude=_longitude;}
    void set_latitude(float _latitude)  {latitude=_latitude;}

private:
    float vitesse;
    float cap;
    float longitude;
    float latitude;
    int id; //Identifiant de la station meteo pour la communication des datas
};
