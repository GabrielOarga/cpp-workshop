#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "BaseShape.h"

class Ellipse : public BaseShape
{
	Q_OBJECT

public:
	Ellipse(QPointF startPoint, QPointF endPoint, QWidget* parent = 0);
	~Ellipse();

	void draw(QPainter& painter) const override;

private:
	QRectF m_rect;
};

#endif //ELLIPSE_H