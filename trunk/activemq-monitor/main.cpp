#include "ActiveMQMonitor.h"

#include <QtCore/QTime>
#include <QtGui>
#include <QtGui/QApplication>
#include "iostream.h"

void DebugOutputHandler(QtMsgType type, const char *msg)
{
	switch (type)
	{
	case QtDebugMsg:
		cerr << "[DEBUG]   : " << msg << "\n";
		break;
	case QtWarningMsg:
		cerr << "[WARNING] : " << msg << "\n";
		break;
	case QtSystemMsg:
		cerr << "[SYSTEM]  : " << msg << "\n";
		break;
	case QtFatalMsg:
		cerr << "[FATAL]   : " << msg << "\n";
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
