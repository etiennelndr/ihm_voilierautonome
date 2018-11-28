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


private slots:
    void on_BtnValider_clicked();

private:
    Ui::Balise_IHM *ui;

    QLineEdit *TxtLongitude_1;
    QLineEdit *TxtLatitude_1;
    QLineEdit *TxtLongitude_2;
    QLineEdit *TxtLatitude_2;
    QLineEdit *TxtLongitude_3;
    QLineEdit *TxtLatitude_3;
    QLineEdit *TxtLongitude_4;
    QLineEdit *TxtLatitude_4;
};



#endif // BALISES_H
