#ifndef SATIONSMETEO_H
#define SATIONSMETEO_H

#include <QDialog>
#include "meteo.h"
#include "stationsmeteo2.h"
#include <QDebug>

namespace Ui {
class sationsmeteo;
}

class sationsmeteo : public QDialog
{
    Q_OBJECT

public:
    explicit sationsmeteo(QWidget *parent = nullptr);
    ~sationsmeteo();

private slots:
    void on_pushButton_clicked();
    void transfer_new_meteo(Meteo);

    signals:
    void new_meteo(Meteo);

private:
    Ui::sationsmeteo *ui;
};

#endif // SATIONSMETEO_H
