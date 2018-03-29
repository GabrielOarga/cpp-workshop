#include "BaseShape.h"

BaseShape::BaseShape(QPointF startPoint, QPointF endPoint, QWidget* parent)
	: QWidget(parent)
	, m_endPoint(endPoint)
	, m_startPoint(startPoint)
{

}

BaseShape::~BaseShape()
{

}
