#include "RealCloud_EDU_PC_DEMO.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RealCloud_EDU_PC_DEMO w;
	w.show();
	return a.exec();
}
