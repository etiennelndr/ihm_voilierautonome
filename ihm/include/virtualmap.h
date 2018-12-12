#ifndef VIRTUALMAP_H
#define VIRTUALMAP_H 1

#include <QMainWindow>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <cmath>
#include "boat.h"
#include "balise.h"
#include <QtGui>
#include <QtCore>
#include <QPainter>


using namespace std;

/**
 * @brief The VirtualMap class
 */
class VirtualMap {
	public:
		VirtualMap(Balise* b1, Balise* b2, Balise* b3, Balise* b4);
		~VirtualMap();

		// Getters
		float get_start_latitude() const;
		float get_start_longitude() const;
		float get_end_latitude() const;
		float get_end_langitude() const;
		// Setters
		void  set_start_latitude(float lat);
		void  set_start_longitude(float lon);
		void  set_end_latitude(float lat);
		void  set_end_longitude(float lon);

		void display_boats(vector<Boat*> boats, QMainWindow* mw);

	private :
		// Ces paramètres sont utilisés pour créer la carte : ils permettent de définir
		// les dimensions de cette dernière
		float start_latitude;
		float start_longitude;
		float end_latitude;
		float end_longitude;

		// Chaque élément de ce vector correspond à une balise physique qui sera placée
		// pour les courses
		vector <Balise*> balises;

		QGraphicsScene* scene = nullptr;
		QRectF* zone		  = nullptr;
		QGraphicsView* vie    = nullptr;

		int scale_lat(float l);
		int scale_lon(float l);
		float angle(float l);
		void set_start_and_end_lat_and_long();
};

inline float VirtualMap::get_start_latitude() const { return start_latitude; }
inline float VirtualMap::get_start_longitude() const { return start_longitude; }
inline float VirtualMap::get_end_latitude() const { return end_latitude; }
inline float VirtualMap::get_end_langitude() const { return end_longitude; }

inline void  VirtualMap::set_start_latitude(float lat) { start_latitude = lat; }
inline void  VirtualMap::set_start_longitude(float lon) { start_longitude = lon; }
inline void  VirtualMap::set_end_latitude(float lat) { end_latitude = lat; }
inline void  VirtualMap::set_end_longitude(float lon) { end_longitude = lon; }

#endif // VIRTUALMAP_H
