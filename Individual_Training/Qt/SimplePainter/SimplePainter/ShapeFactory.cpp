#include "ShapeFactory.h"

#include "BaseShape.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Point.h"
#include "Text.h"
#include "Line.h"

#include <QDebug>

ShapeFactory::ShapeFactory(void)
{

}

ShapeFactory::~ShapeFactory(void)
{

}

std::unique_ptr<BaseShape> ShapeFactory::createShape (
	QPointF startPosition
	, QPointF endPosition
	, ShapeType shapeType
	, QWidget *parent
	)
{
	std::unique_ptr<BaseShape> shape;

	switch(shapeType) {
	case ShapeType::Rectangle:
		{
			std::unique_ptr<BaseShape> rect(new Rectangle(startPosition, endPosition, parent));
			shape = std::move(rect);
			break;
		}
	case ShapeType::Ellipse:
		{
			std::unique_ptr<BaseShape> ellipse(new Ellipse(startPosition, endPosition, parent));
			shape = std::move(ellipse);
			break;
		}
	case ShapeType::Point:
		{
			std::unique_ptr<BaseShape> point(new Point(startPosition, parent));
			shape = std::move(point);
			break;
		}
	case ShapeType::Text:
		{
			std::unique_ptr<BaseShape> text(new Text(startPosition, endPosition, parent));
			shape = std::move(text);
			break;
		}
	case ShapeType::Line:
		{
			std::unique_ptr<BaseShape> line(new Line(startPosition, endPosition, parent));
			shape = std::move(line);
			break;
		}
	default:
		{
			qFatal("RenderArea.cpp --> ");
		}
	}

	return shape;
}