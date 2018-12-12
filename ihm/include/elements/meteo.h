#ifndef METEO_H
#define METEO_H


/**
 * @brief The Meteo class
 */
class Meteo {
	public:
		// Constructors
		Meteo(int id, float lat, float lon);
		Meteo(bool _end_of_transfer);

		// Getters
		float  get_vitesse();
		float  get_cap();
		float  get_longitude();
		float  get_latitude();
		float* get_vitesse_addr();
		float* get_cap_addr();
		float* get_longitude_addr();
		float* get_latitude_addr();
		int    get_id();
		bool   get_end_of_transfer() const;

		// Setters
		void set_vitesse(float _vitesse);
		void set_cap(float _cap);
		void set_longitude(float _longitude);
		void set_latitude(float _latitude);

	private:
		float vitesse;
		float cap;
		float longitude;
		float latitude;
		int id; // Identifiant de la station meteo pour la communication des datas
		bool end_of_transfer = false; // Permet de savoir quand le transfert de stations meteos est termine (cf StationsMeteo2)
};


inline float  Meteo::get_vitesse()				  { return vitesse; }
inline float  Meteo::get_cap()					  { return cap; }
inline float  Meteo::get_longitude()			  { return longitude; }
inline float  Meteo::get_latitude()			  { return latitude; }
inline float* Meteo::get_vitesse_addr()		  { return &vitesse; }
inline float* Meteo::get_cap_addr()			  { return &cap; }
inline float* Meteo::get_longitude_addr()		  { return &longitude; }
inline float* Meteo::get_latitude_addr()		  { return &latitude; }
inline int    Meteo::get_id()					  { return id; }
inline bool   Meteo::get_end_of_transfer() const { return end_of_transfer; }

inline void Meteo::set_vitesse(float _vitesse)		{ vitesse = _vitesse; }
inline void Meteo::set_cap(float _cap)				{ cap = _cap; }
inline void Meteo::set_longitude(float _longitude) { longitude = _longitude; }
inline void Meteo::set_latitude(float _latitude)   { latitude = _latitude; }


#endif // METEO_H
