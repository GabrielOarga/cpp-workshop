#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "ShapeType.h"
#include <memory>

class BaseShape;
class QPointF;
class QWidget;
 
class ShapeFactory
{
public:
	ShapeFactory(void);
	~ShapeFactory(void);

	static std::unique_ptr<BaseShape> createShape(QPointF startPosition
		, QPointF endPosition, ShapeType shapeType, QWidget* parent = 0);
};

#endif //SHAPEFACTORY_H