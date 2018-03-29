#include "Line.h"

#include <QPainter>

Line::Line(QPointF startPoint, QPointF endPoint, QWidget* parent)
	: BaseShape(startPoint, endPoint, parent)
{

}

Line::~Line()
{

}

void Line::draw(QPainter& painter) const
{
	painter.drawLine(m_startPoint, m_endPoint);
}
