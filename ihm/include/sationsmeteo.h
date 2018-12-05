#ifndef SATIONSMETEO_H
#define SATIONSMETEO_H 1

#include <QDialog>
#include "meteo.h"
#include "stationsmeteo2.h"
#include <QDebug>
namespace Ui {
class StationsMeteo;
}

class StationsMeteo : public QDialog
{
    Q_OBJECT

public:
    explicit StationsMeteo(QWidget *parent = nullptr);
    ~StationsMeteo();

private slots:
    void on_pushButton_clicked();
    void transfer_new_meteo(Meteo);

    signals:
    void new_meteo(Meteo);

private:
    Ui::StationsMeteo *ui = nullptr;
};

#endif // SATIONSMETEO_H
