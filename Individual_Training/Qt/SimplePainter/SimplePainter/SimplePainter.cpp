// SimplePainter.cpp : Defines the entry point for the console application.
//

#include "PainterMainWindow.h"

#include <QDebug> //For testing only
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	PainterMainWindow mainWindow;
	mainWindow.show();

    return app.exec();
}

/*TODO:
	- Add Text dialog to enter text and other options
	- Add Remove function(rightclick or button + click
	- Move function for shapes
	- Caching (save/load)
*/