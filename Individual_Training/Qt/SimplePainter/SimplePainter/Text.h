#ifndef TEXT_H
#define TEXT_H

#include "BaseShape.h"

class Text : public BaseShape
{
	Q_OBJECT

public:
	Text(QPointF startPoint, QPointF endPoint, QWidget* parent = 0);
	~Text();
	
	void draw(QPainter& painter) const override;

private:
	
	QRectF m_rect;
};

#endif //TEXT_H

