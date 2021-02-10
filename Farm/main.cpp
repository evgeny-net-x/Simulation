#include "farm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Farm w;
	w.show();
	return a.exec();
}
