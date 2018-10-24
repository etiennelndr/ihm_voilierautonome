#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDialog>
#include<QKeyEvent>
#include "client.h"
class QPushButton;
class QRadioButton;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void on_RadioControle_clicked();
        void on_BtnConx_clicked();
        void on_BtnDeconx_clicked();
        void on_Btn_Exit_clicked();

    public:
        void getvitesse(float v);
        void getcap(float c);
        void getlongitude(float lg);
        void getlatitude(float la);
        void getgite(float g);
        void gettangage(float t);
        void getbarre(float b);
        void getvoile(float v);

    private:
         float vitesse, cap, longitude, latitude, gite,tangage ,barre, voile;
        // Client client;


    private:
        Ui::MainWindow *ui;
        void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
