#ifndef BALISES_H
#define BALISES_H 1

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <string>
#include <QString>
#include <iostream>
#include <vector>
#include <sstream>
#include <QtGlobal>
#include <QTime>
#include <QDebug>

#include "balise.h"

namespace Ui {
	class Balise_IHM;
}

/**
 * @brief The Balise_IHM class
 */
class Balise_IHM : public QDialog {
    Q_OBJECT

	public:
		explicit Balise_IHM(QWidget *parent = nullptr);
		~Balise_IHM();


	private slots:
		void on_BtnValider_clicked();

	signals:
		void new_balise(Balise);

	private:
		Ui::Balise_IHM *ui = nullptr;

		QLineEdit *TxtLongitude_1 = nullptr;
		QLineEdit *TxtLatitude_1  = nullptr;
		QLineEdit *TxtLongitude_2 = nullptr;
		QLineEdit *TxtLatitude_2  = nullptr;
		QLineEdit *TxtLongitude_3 = nullptr;
		QLineEdit *TxtLatitude_3  = nullptr;
		QLineEdit *TxtLongitude_4 = nullptr;
		QLineEdit *TxtLatitude_4  = nullptr;
};



#endif // BALISES_H
