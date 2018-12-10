#ifndef BALISES_H
#define BALISES_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <string>
#include <QString>
#include <iostream>
#include <vector>
#include <sstream>
#include <QtGlobal>
#include <QTime>
#include <QDebug>

#include "balise.h"

namespace Ui {
class Balise_IHM;
}

class Balise_IHM : public QDialog
{
    Q_OBJECT

public:
    explicit Balise_IHM(QWidget *parent = nullptr);
    ~Balise_IHM();


private slots:
    void on_BtnValider_clicked();

    signals:
        void new_balise(Balise);

private:
    Ui::Balise_IHM *ui;

    //Longitude du balise 1
    QLineEdit *TxtLongitude_1;
    //Latitude du balise 1
    QLineEdit *TxtLatitude_1;

    //Longitude du balise 2
    QLineEdit *TxtLongitude_2;  
    //Latitude du balise 2
    QLineEdit *TxtLatitude_2;

    //Longitude du balise 3
    QLineEdit *TxtLongitude_3;
    //Latitude du balise 3
    QLineEdit *TxtLatitude_3;

    //Longitude du balise 4
    QLineEdit *TxtLongitude_4;
    //Latitude du balise 4
    QLineEdit *TxtLatitude_4;
};



#endif // BALISES_H
