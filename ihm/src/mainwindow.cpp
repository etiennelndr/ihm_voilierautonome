#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "mainwindow.h"
#include<QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QKeyEvent>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QRadioButton>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
     ui->setupUi(this);
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
    delete ui;
    delete client;
}

/**
 * @brief MainWindow::on_RadioControle_clicked
 */
void MainWindow::on_RadioControle_clicked() {
    if(ui->RadioControle->isChecked()) {
        QMessageBox::information(this,"Informations autour du bateau","Utiliser les fleches du clavier pour contrôler le bateau");
    } else {

    }
}

/**
 * @brief MainWindow::keyPressEvent
 * @param event
 */
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(ui->RadioControle->isChecked()) {
        if(event->key()==Qt::Key_Up) {
            voile+=0.5;
            //client.set_voile(&voile);
        } else if (event->key()==Qt::Key_Down) {
            voile-=0.5;
            //client.set_voile(voile);
        } else if (event->key()==Qt::Key_Right) {
            barre += 0.5;
            //client.set_barre(barre);
        } else if (event->key()==Qt::Key_Left) {
            barre -= 0.5;
            //client.set_barre(barre);
        }
    } else
      QMessageBox::information(this,"Error","Tu ne peux pas contrôler le bateau");
}


/**
 * @brief MainWindow::on_Btn_Exit_clicked
 */
void MainWindow::on_Btn_Exit_clicked() {
   close();
}

/**
 * @brief MainWindow::on_BtnConxDeconx_clicked
 */
void MainWindow::on_BtnConxDeconx_clicked() {
    if(ui->BtnConxDeconx->text() ==  "Connexion") {
        ui->BtnConxDeconx->setText(("Deconnexion"));
        client = new ClientTcp(QString("127.0.0.1"), 4000, QString("Etienne"));
    } else {
        ui->BtnConxDeconx->setText("Connexion");
        delete client;
        client = nullptr;
    }
}
