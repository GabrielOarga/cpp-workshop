#include "Point.h"

#include <QPainter>

Point::Point(QPointF startPoint, QWidget* parent)
	: BaseShape(startPoint, startPoint ,parent)
{

}

Point::~Point()
{

}

void Point::draw(QPainter& painter) const
{
	painter.drawPoint(m_startPoint);
}
