#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QWidget>

class BaseDialog : public QWidget
{
	//Q_OBJECT

public:
	explicit BaseDialog(QWidget* parent = 0);
	virtual ~BaseDialog();

};

#endif BASEDIALOG_H