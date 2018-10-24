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

}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
}

<<<<<<< HEAD
void MainWindow::on_BtnConx_clicked()
{
    connect(client,signal(set_vitesse(float)),this, slot(getvitesse(float)));
=======
void MainWindow::on_BtnConx_clicked() {
    //connect signal(client,set_vitesse(float)),this, slot(getvitesse(float v)));
>>>>>>> f7dafe32086e13f2c536ac1322eed199f896b92d
}

void MainWindow::on_BtnDeconx_clicked()
{
void MainWindow::on_BtnDeconx_clicked() {

}

void MainWindow::on_Btn_Exit_clicked()
{
void MainWindow::on_Btn_Exit_clicked() {
   close();
}
