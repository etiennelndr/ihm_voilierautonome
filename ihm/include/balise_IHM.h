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

private slots:
    void on_bouton_valider_clicked();

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



#endif // BALISES_H
