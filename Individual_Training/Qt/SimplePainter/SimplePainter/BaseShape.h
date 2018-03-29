#ifndef BASESHAPE_H
#define BASESHAPE_H

#include <QWidget>
#include <QPointF>

class QPainter;

class BaseShape : public QWidget
{
	Q_OBJECT

public:
	BaseShape(QPointF startPoint, QPointF endPoint, QWidget* parent = 0);
	virtual ~BaseShape();

	virtual void draw(QPainter& painter) const = 0;

protected:
	QPointF m_endPoint;
	QPointF m_startPoint;
};

#endif //BASESHAPE_H
