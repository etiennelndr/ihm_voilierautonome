#ifndef STATIONSMETEO2_H
#define STATIONSMETEO2_H 1

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QTextEdit>
#include <vector>
#include "meteo.h"

using namespace std;

namespace Ui {
class StationsMeteo2;
}

class Stationsmeteo2 : public QDialog
{
    Q_OBJECT

    public:
        explicit Stationsmeteo2(QWidget *parent = nullptr, int nb=0);
        ~Stationsmeteo2();
    signals:
        void new_meteo(Meteo);

    private:
        Ui::StationsMeteo2 *ui = nullptr;
    //    QLabel *labels[NumGridRows];
    //    QLabel *labelsBalise[NumGridRows];
    //    QLabel *labelsID[NumGridRows];
    //    QLineEdit *lineEditsID[NumGridRows];
    //    QLineEdit *lineEdits[NumGridRows];
        vector<QLabel*> labelsLongitude;
        vector<QLabel*> labelsLatitude;
        vector<QLabel*> labelsBalise;
        vector<QLabel*> labelsID;

        // ID des stations meteos
        vector<QLineEdit*> lineEditsID;
        // Longitude des stations meteos
        vector<QLineEdit*> lineEditsLongitude;
        // Latitude des stations meteos
        vector<QLineEdit*> lineEditsLatitude;

        QGroupBox *gridGroupBox = nullptr;
        QWidget      w;
        //QGridLayout* gl     = new QGridLayout(&w);

    private slots :
        void on_BtnValider_clicked();
};

#endif // STATIONSMETEO2_H
