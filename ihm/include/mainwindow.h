#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

        //Receive data from client
        void receive_longitude(float l, int id_concern);
        void receive_latitude(float l, int id_concern);
        void receive_cap(float c, int id_concern);
        void receive_vitesse(float v, int id_concern);
        void receive_gite(float g, int id_concern);
        void receive_tangage(float t, int id_concern);
        void receive_barre(float b, int id_concern);
        void receive_voile(float v, int id_concern);
        void add_new_boat(int id_concern);
        void display_Boussle(QMainWindow* mw);
        void display_Gite_Tangage(QMainWindow* mw);



private:
        sationsmeteo *station_IHM;
        Balise_IHM *balise_IHM;



private slots:
        void on_actionStations_triggered();
        void on_actionBalise_triggered();
        void add_balise(Balise);
        void add_meteo(Meteo);

        void on_combo_activated(const QString &arg1);

private:
        float delta_barre, delta_voile;
        bool connected;
        ClientTcp* client=nullptr;
        int my_id;
        Ui::MainWindow *ui;
        vector<Boat*> boats;
        vector<Meteo*> meteos;
        vector<Balise*> balises;
        VirtualMap* virtual_map= nullptr;

        void keyPressEvent(QKeyEvent *event);
        void create_connections();
        Boat* get_boat(int id);
        Meteo* get_meteo(int id);

        QMutex mtx;
        QComboBox *combobox12;
};

#endif // MAINWINDOW_H
