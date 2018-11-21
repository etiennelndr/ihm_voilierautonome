#ifndef BALISES_H
#define BALISES_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class balises;
}

class balises : public QDialog
{
    Q_OBJECT

public:
    explicit balises(QWidget *parent = nullptr);

    QLineEdit *getTxtLongitude_1() const;
    QLineEdit *getTxtLatitude_1() const;
    QLineEdit *getTxtLongitude_2() const;
    QLineEdit *getTxtLatitude_2() const;
    QLineEdit *getTxtLongitude_3() const;
    QLineEdit *getTxtLatitude_3() const;
    QLineEdit *getTxtLongitude_4() const;
    QLineEdit *getTxtLatitude_4() const;

private:
    Ui::balises *ui;
    QLineEdit *TxtLongitude_1;
    QLineEdit *TxtLatitude_1;
    QLineEdit *TxtLongitude_2;
    QLineEdit *TxtLatitude_2;
    QLineEdit *TxtLongitude_3;
    QLineEdit *TxtLatitude_3;
    QLineEdit *TxtLongitude_4;
    QLineEdit *TxtLatitude_4;
};

class Balise{
public:
    Balise();
    //get
    float get_latitude() const        {return latitude;}
    float get_longitude() const       {return longitude;}
    //set
    float set_latitude() const          {return latitude;}
    float set_langitude() const         {return longitude;}


private:
    float latitude;
    float longitude;
    balises choice;
};

#endif // BALISES_H
