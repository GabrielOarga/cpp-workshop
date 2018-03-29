#ifndef LINE_H
#define LINE_H

#include "BaseShape.h"

class Line : public BaseShape
{
	Q_OBJECT 

public:
	Line(QPointF startPoint, QPointF endPoint, QWidget* parent = 0);
	~Line();
	
	void draw(QPainter& painter) const override;

private:

};

#endif //LINE_H
