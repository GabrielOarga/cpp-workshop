#ifndef PAINTERMAINWIDNOW_H
#define PAINTERMAINWIDNOW_H

#include <QWidget>

class QLabel;
class QSpinBox;
class QComboBox;
class QCloseEvent;

class RenderArea;

class PainterMainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit PainterMainWindow(QWidget* parent = 0);
	void closeEvent(QCloseEvent * event) override;

private slots:
	void onShapeSelectionChanged();

private:
	QLabel* m_shapeLabel;
	QComboBox* m_shapeComboBox;
	RenderArea* m_renderArea;
};

#endif //PAINTERMAINWIDNOW_H