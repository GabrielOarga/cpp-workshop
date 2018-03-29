#ifndef POINT_H
#define POINT_H

#include "BaseShape.h"

class Point : public BaseShape
{
	Q_OBJECT

public:
	Point(QPointF startPoint, QWidget* parent = 0);
	~Point();
	
	void draw(QPainter& painter) const override;

private:

};

#endif //POINT_H

