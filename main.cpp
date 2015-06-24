#include "face_detection.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Face_detection w;
	w.show();
	return a.exec();
}
