#include "Ellipse.h"

#include <QRectF>
#include <QPainter>

Ellipse::Ellipse(QPointF startPoint, QPointF endPoint, QWidget* parent)
	: BaseShape(startPoint, endPoint, parent)
	, m_rect(m_startPoint, m_endPoint)
{

}

Ellipse::~Ellipse()
{

}

void Ellipse::draw(QPainter& painter) const
{
	painter.drawEllipse(m_rect);
}