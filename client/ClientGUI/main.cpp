#include <qapplication.h>
#include "LoginView.h"
#include "Protocols.h"
#include <qthread.h>

int main(int n, char** arg)
{
	QApplication app(n, arg);
	
	LoginView view(NULL);
	view.show();

	return app.exec();
}