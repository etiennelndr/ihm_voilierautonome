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
#include "meteo.h"

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
        explicit MainWindow(QWidget *parent = 0);
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

    private:
        float delta_barre, delta_voile;
        bool connected;
        ClientTcp* client=nullptr;
        int my_id;
        Ui::MainWindow *ui;
        vector<Boat*> boats;
        vector<Meteo*> meteos;
        VirtualMap* virtual_map;

        void keyPressEvent(QKeyEvent *event);
        void create_connections();
        Boat* get_boat(int id);

        QMutex mtx;
};

#endif // MAINWINDOW_H
