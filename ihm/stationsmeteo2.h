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
namespace Ui {
class stationsmeteo2;
}

class stationsmeteo2 : public QDialog
{
    Q_OBJECT

public:
    explicit stationsmeteo2(QWidget *parent = nullptr, int nb=0);
    ~stationsmeteo2();
    enum {NumGridRows = 15};
private:
    Ui::stationsmeteo2 *ui;
    QLabel *labels[NumGridRows];
    QLabel *labelsBalise[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QGroupBox *gridGroupBox;
    QWidget      w;
    QGridLayout* gl     = new QGridLayout(&w);
};

#endif // STATIONSMETEO2_H
