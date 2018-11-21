#ifndef SATIONSMETEO_H
#define SATIONSMETEO_H

#include <QDialog>

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

private:
    Ui::sationsmeteo *ui;
};

#endif // SATIONSMETEO_H
