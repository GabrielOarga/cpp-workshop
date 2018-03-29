#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "BaseShape.h"

class Rectangle : public BaseShape
{
	Q_OBJECT

public:
	Rectangle(QPointF startPoint, QPointF endPoint, QWidget* parent = 0);
	~Rectangle();
	
	void draw(QPainter& painter) const override;

private:
	QRectF m_rect;
};

#endif //RECTANGLE_H
