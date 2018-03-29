#include "Text.h"

#include <QRectF>
#include <QPainter>

#include <QTextEdit>
#include <QGridLayout>

Text::Text(QPointF startPoint, QPointF endPoint, QWidget* parent)
	: BaseShape(startPoint, endPoint, parent)
	, m_rect(m_startPoint, m_endPoint)
{
}

Text::~Text()
{

}

void Text::draw(QPainter& painter) const
{
	painter.drawRect(m_rect);
}
