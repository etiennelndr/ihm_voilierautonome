#ifndef STATIONSMETEO2_H
#define STATIONSMETEO2_H

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
class stationsmeteo2;
}

class Stationsmeteo2 : public QDialog
{
    Q_OBJECT

    public:
        explicit Stationsmeteo2(QWidget *parent = nullptr, int nb=0);
        ~Stationsmeteo2();
    //    enum {NumGridRows = 15};

    signals:
        void new_meteo(Meteo);

    private:
        Ui::stationsmeteo2 *ui;
    //    QLabel *labels[NumGridRows];
    //    QLabel *labelsBalise[NumGridRows];
    //    QLabel *labelsID[NumGridRows];
    //    QLineEdit *lineEditsID[NumGridRows];
    //    QLineEdit *lineEdits[NumGridRows];
        vector<QLabel*> labelsLongitude;
        vector<QLabel*> labelsLatitude;
        vector<QLabel*> labelsBalise;
        vector<QLabel*> labelsID;
        vector<QLineEdit*> lineEditsID;
        vector<QLineEdit*> lineEditsLongitude;
        vector<QLineEdit*> lineEditsLatitude;

        QGroupBox *gridGroupBox;
        QWidget      w;
        QGridLayout* gl     = new QGridLayout(&w);

    private slots :
        void on_BtnValider_clicked();
};

#endif // STATIONSMETEO2_H
