#ifndef RENDERAREA_H
#define RENDERAREA_H

#define RENDERAREA_LOGGING

#include "ShapeType.h"

#include <QWidget>
#include <QPointF>
#include <QMetaType>
#include <memory>

class BaseShape;

class RenderArea : public QWidget
{
	Q_OBJECT

public:
	explicit RenderArea(QWidget* parent  = 0);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

public slots:
	void setShapeType(ShapeType shapeType);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	std::list<std::unique_ptr<BaseShape>> m_shapeList;
	std::unique_ptr<BaseShape> m_preview;
	ShapeType m_shapeType;
	QPointF m_endPoint;
	QPointF m_startPoint;
	bool m_isDrawing;

	void resetPoints();
};

Q_DECLARE_METATYPE(ShapeType)

#endif //RENDERAREA_H
