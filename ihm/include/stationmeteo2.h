#ifndef STATIONMETEO2_H
#define STATIONMETEO2_H

#include <QDialog>

namespace Ui {
class stationMeteo2;
}

class stationMeteo2 : public QDialog
{
    Q_OBJECT

public:
    explicit stationMeteo2(QWidget *parent = nullptr);
    ~stationMeteo2();

private:
    Ui::stationMeteo2 *ui;
};

#endif // STATIONMETEO2_H
