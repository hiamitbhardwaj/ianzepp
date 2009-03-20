#include "ActiveMQMonitor.h"

#include <QtCore/QTime>
#include <QtGui>
#include <QtGui/QApplication>
#include <iostream>

void DebugOutputHandler(QtMsgType type, const char *msg)
{
	switch (type)
	{
	case QtDebugMsg:
		std::cerr << "[DEBUG]   : " << msg << std::endl;
		break;
	case QtWarningMsg:
		std::cerr << "[WARNING] : " << msg << std::endl;
		break;
	case QtSystemMsg:
		std::cerr << "[SYSTEM]  : " << msg << std::endl;
		break;
	case QtFatalMsg:
		std::cerr << "[FATAL]   : " << msg << std::endl;
		abort(); // dump core on purpose
	}
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qInstallMsgHandler(DebugOutputHandler);

	ActiveMQMonitor w;
	w.show();
	return a.exec();
}
