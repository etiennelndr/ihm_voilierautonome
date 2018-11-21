#ifndef BALISES_H
#define BALISES_H

#include <QDialog>

namespace Ui {
class balises;
}

class balises : public QDialog
{
    Q_OBJECT

public:
    explicit balises(QWidget *parent = nullptr);
    ~balises();

private:
    Ui::balises *ui;
};

#endif // BALISES_H
