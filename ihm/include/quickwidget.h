#ifndef QUICKWIDGET_H
#define QUICKWIDGET_H 1

#include <QQuickWidget>

class QuickWidget : public QQuickWidget {
	public:
		QuickWidget(QWidget *parent = Q_NULLPTR) : QQuickWidget(parent) {
			setSource(QUrl("qrc:/mapviewer.qml"));
			setResizeMode(QQuickWidget::SizeRootObjectToView);
		}
};

#endif // QUICKWIDGET_H