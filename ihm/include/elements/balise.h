#ifndef BALISE_H
#define BALISE_H


/**
 * @brief The Balise class
 */
class Balise {
	public:
		Balise(float _latitude, float _longitude);
		Balise(bool _end_of_transfer);
		//get
		float get_latitude() const         { return latitude; }
		float get_longitude() const        { return longitude; }
		bool  get_end_of_transfer() const  { return end_of_transfer; }
		//set
		float set_latitude() const          { return latitude; }
		float set_langitude() const         { return longitude; }

	private:
		float latitude;
		float longitude;
		bool end_of_transfer = false; // Permet de savoir quand le transfert de balises est termine (cf balise_IHM)
};

#endif // BALISE_H
