#include "PainterMainWindow.h"

#include "RenderArea.h"
//#include "BaseDialog.h"

#include <vector>
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QCloseEvent>
#include <QMessageBox>

PainterMainWindow::PainterMainWindow(QWidget* parent)
	: QWidget(parent)
	, m_shapeLabel(new QLabel)
	, m_shapeComboBox(new QComboBox)
	, m_renderArea(new RenderArea)
{
	std::vector<QString> shapeTypeName; //TODO: Const?
	shapeTypeName.push_back("Rectangle");
	shapeTypeName.push_back("Ellipse");
	shapeTypeName.push_back("Point");
	shapeTypeName.push_back("Text");
	shapeTypeName.push_back("Line");

	std::vector<ShapeType> shapeType; //TODO: Const?
	shapeType.push_back(ShapeType::Rectangle);
	shapeType.push_back(ShapeType::Ellipse);
	shapeType.push_back(ShapeType::Point);
	shapeType.push_back(ShapeType::Text);
	shapeType.push_back(ShapeType::Line);

	for (unsigned int i = 0; i < shapeType.size(); ++i) {
		m_shapeComboBox->addItem(shapeTypeName.at(i), static_cast<int>(shapeType.at(i)));
	}

	m_shapeLabel->setText(tr("&Shape:"));
	m_shapeLabel->setBuddy(m_shapeComboBox);

	connect(m_shapeComboBox, SIGNAL(activated(int)),
		this, SLOT(onShapeSelectionChanged()));

	QVBoxLayout* rightMenuLayout = new QVBoxLayout;
	rightMenuLayout->addWidget(m_shapeLabel);
	rightMenuLayout->addWidget(m_shapeComboBox);
	rightMenuLayout->addStretch();

	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->addWidget(m_renderArea, 0, 0, 1, 1);
	mainLayout->addLayout(rightMenuLayout, 0, 1, 1, 1);
	
	setLayout(mainLayout);
	
	setWindowTitle("Simple Painter");
}

void PainterMainWindow::onShapeSelectionChanged()
{
	const ShapeType shapeType = ShapeType(m_shapeComboBox->itemData(m_shapeComboBox->currentIndex()).toInt());
	m_renderArea->setShapeType(shapeType);
}

void PainterMainWindow::closeEvent(QCloseEvent *event) 
{
	//TODO: Halt the application here to ask for caching
}