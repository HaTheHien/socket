#include <qapplication.h>
#include "LoginView.h"

int main(int n, char** arg)
{
	QApplication app(n, arg);
	
	LoginView view(NULL);
	view.show();

	return app.exec();
}