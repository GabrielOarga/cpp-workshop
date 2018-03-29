#include "RenderArea.h"

#include "BaseShape.h"
#include "ShapeFactory.h"

#include <QList>
#include <QDebug>
#include <QString>
#include <QPainter>
#include <QMouseEvent>

RenderArea::RenderArea(QWidget* parent)
	: QWidget(parent)
	, m_shapeType(ShapeType::Rectangle)
	, m_endPoint(QPointF(0,0))
	, m_startPoint(QPointF(0,0))
{
}

QSize RenderArea::minimumSizeHint() const
{
	return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
	return QSize(400, 200);
}

void RenderArea::setShapeType(ShapeType shapeType)
{
	if (m_shapeType != shapeType)
		m_shapeType = shapeType;
}

void RenderArea::paintEvent(QPaintEvent* event)
{
#ifdef RENDERAREA_LOGGING
	qDebug() << "paint event";
#endif RENDERAREA_LOGGING
	QPainter painter(this);

	QRect rect(0, 0, width() - 1, height() - 1);
	painter.drawRect(rect);

	if (m_isDrawing) {
		m_preview = std::unique_ptr<BaseShape>(ShapeFactory::createShape(m_startPoint, m_endPoint, m_shapeType, this));
		m_preview->draw(painter);
	}

	for (auto iter = m_shapeList.cbegin(); iter != m_shapeList.cend(); iter++) {
		(*iter)->draw(painter);
	}
}

void RenderArea::mouseMoveEvent(QMouseEvent* event)
{
	m_endPoint = QPointF(event->posF().x(), event->posF().y());
#ifdef RENDERAREA_LOGGING
	qDebug() << "mouse move event";	
	qDebug() << "updated end point: " << m_endPoint;
#endif //RENDERAREA_LOGGING
	update();
}

void RenderArea::mousePressEvent(QMouseEvent* event)
{
	m_isDrawing = true;
	m_startPoint = QPointF(event->posF().x(), event->posF().y());
	m_endPoint = m_startPoint; 

#ifdef RENDERAREA_LOGGING
	qDebug() << "mouse pressed event";
	qDebug() << "start point: " << m_startPoint;
	qDebug() << "end point: " << m_endPoint;
#endif //RENDERAREA_LOGGING
}

void RenderArea::mouseReleaseEvent(QMouseEvent* event)
{
#ifdef RENDERAREA_LOGGING
	qDebug() << "mouse released event";
	qDebug() << "start point: " << m_startPoint;
	qDebug() << "end point: " << m_endPoint;
#endif //RENDERAREA_LOGGING

	m_isDrawing = false;

	std::unique_ptr<BaseShape> base = std::move(ShapeFactory::createShape(m_startPoint, m_endPoint, m_shapeType, this));

	m_shapeList.push_back(std::move(base));
	resetPoints();
	update();
}

void RenderArea::resetPoints()
{
	m_startPoint = QPointF(0.0f, 0.0f);
	m_endPoint = QPointF(0.0f, 0.0f);
}