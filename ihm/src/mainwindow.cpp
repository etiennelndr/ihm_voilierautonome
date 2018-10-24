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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
}

MainWindow::~MainWindow()
{
     delete ui;
}

void MainWindow::on_RadioControle_clicked()
{
    if(ui->RadioControle->isChecked()){
    QMessageBox::information(this,"Information autour de bateau","Utiliser les fleches du clavier pour controller le bateau");
    }else if(ui->RadioControle->isChecked())
    {}
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->RadioControle->isChecked())
    {
    if(event->key()==Qt::Key_Up){
        voile+=0.5;
        client.set_voile(&voile);
    }
    else if (event->key()==Qt::Key_Down) {
        voile-=0.5;
        client.set_voile(voile);
    }
    else if (event->key()==Qt::Key_Right) {
       barre += 0.5;
       client.set_barre(barre);
    }
    else if (event->key()==Qt::Key_Left) {
        barre -= 0.5;
        client.set_barre(barre);
    }
    }else
      QMessageBox::information(this,"Error","Tu ne peut pas controller le bateau");
}

void MainWindow::on_BtnConx_clicked()
{
    connect(client,signal(set_vitesse(float)),this, slot(getvitesse(float)));
}

void MainWindow::on_BtnDeconx_clicked()
{

}

void MainWindow::on_Btn_Exit_clicked()
{
   close();
}
