#include "Rectangle.h"

#include <QRectF>
#include <QPainter>

Rectangle::Rectangle(QPointF startPoint, QPointF endPoint, QWidget* parent)
	: BaseShape(startPoint, endPoint, parent)
	, m_rect(startPoint, endPoint)
{

}

Rectangle::~Rectangle()
{

}

void Rectangle::draw(QPainter& painter) const
{
	painter.drawRect(m_rect);
}