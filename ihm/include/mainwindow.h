#ifndef MAINWINDOW_H
#define MAINWINDOW_H 1

#include <QMainWindow>
#include <QDialog>
#include <QColor>
#include <vector>
#include <QKeyEvent>
#include <QMutex>
#include "client.h"
#include "boat.h"
#include "virtualmap.h"
#include "sationsmeteo.h"
#include "balise_IHM.h"
#include "stationsmeteo2.h"
#include "meteo.h"
#include "balise.h"
#include <QGraphicsView>
#include <QComboBox>
#include <QLine>
#include <QVector>
#include<QtCore>
#include<QtGui>


class QPushButton;
class QRadioButton;

using namespace std;

namespace Ui {
    class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0,int nb=0);
        ~MainWindow();
        virtual void paintEvent(QPaintEvent *event);

    public slots:
        void on_RadioControle_clicked();
        void on_BtnConxDeconx_clicked();
        void on_Btn_Exit_clicked();
        void set_connexion(bool status);

        // Receive data from client
        void receive_longitude(float l, int id_concern);
        void receive_latitude(float l, int id_concern);
        void receive_cap(float c, int id_concern);
        void receive_vitesse(float v, int id_concern);
        void receive_gite(float g, int id_concern);
        void receive_tangage(float t, int id_concern);
        void receive_barre(float b, int id_concern);
        void receive_voile(float v, int id_concern);

        void add_new_boat(int id_concern);

        void display_Boussole();
        void display_Gite_Tangage();

	private:
        StationsMeteo *station_IHM = nullptr;
        Balise_IHM *balise_IHM     = nullptr;

	private slots:
        // pour afficher le fenetre des stations meteos
        void on_actionStations_triggered();
        // pour afficher le fenetre des balises
        void on_actionBalise_triggered();
        void add_balise(Balise);
        void add_meteo(Meteo);
        void Rotate_gite_tangage();
        void Rotate_Boussle(Meteo);

	private:
        float delta_barre, delta_voile;
        bool connected;
        ClientTcp* client = nullptr;
        int my_id;
        Ui::MainWindow *ui = nullptr;
        vector<Boat*> boats;
        vector<Meteo*> meteos;
        vector<float> angle;
        vector<Balise*> balises;
        VirtualMap* virtual_map = nullptr;

        void keyPressEvent(QKeyEvent *event);
        void create_connections();
        Boat* get_boat(int id);
        Meteo* get_meteo(int id);

        QMutex mtx;
        QComboBox *combobox12 = nullptr;
        QLine* line_5 = nullptr;
};

#endif // MAINWINDOW_H

