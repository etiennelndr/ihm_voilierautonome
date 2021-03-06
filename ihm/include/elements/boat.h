#ifndef BOAT_H
#define BOAT_H

#include <QColor>

/**
 * @brief The Boat class
 */
class Boat {
public:
    Boat(int id, bool is_mine, int r, int g, int b);

    //getters
    float  get_vitesse()        {return vitesse;}
    float  get_cap()            {return cap;}
    float  get_longitude()      {return longitude;}
    float  get_latitude()       {return latitude;}
    float  get_gite()           {return gite;}
    float  get_tangage()        {return tangage;}
    float  get_barre()          {return barre;}
    float  get_voile()          {return voile;}
    float* get_vitesse_addr()   {return &vitesse;}
    float* get_cap_addr()       {return &cap;}
    float* get_longitude_addr() {return &longitude;}
    float* get_latitude_addr()  {return &latitude;}
    float* get_gite_addr()      {return &gite;}
    float* get_tangage_addr()   {return &tangage;}
    float* get_barre_addr()     {return &barre;}
    float* get_voile_addr()     {return &voile;}
    bool   get_is_mine()        {return is_mine;}
    int    get_id()             {return id;}
    QColor get_color()         {return *color;}

    //setters
    void set_vitesse(float _vitesse)    {vitesse=_vitesse;}
    void set_cap(float _cap)            {cap=_cap;}
    void set_longitude(float _longitude){longitude=_longitude;}
    void set_latitude(float _latitude)  {latitude=_latitude;}
    void set_tangage(float _tangage)    {tangage=_tangage;}
    void set_gite(float _gite)          {gite=_gite;}
    void set_barre(float _barre)        {barre=_barre;}
    void set_voile(float _voile)        {voile=_voile;}

private:
    float vitesse=0.0f;
    float cap=0.0f;
    float longitude=0.0f;
    float latitude=0.0f;
    float gite=0.0f;
    float tangage=0.0f;
    float barre=0.0f;
    float voile=0.0f;
    bool  is_mine=false; //Est-ce que ce bateau est celui que je controle
    int   id; //Identifiant du bateau pour la communication des data
    QColor* color;
};

#endif // BOAT_H
