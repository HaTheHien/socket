#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "ClientSocket.h"
#include <QStringList>
#include <QString>
#include <QStringListModel>

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView();
    void setClientSocket(ClientSocket* sock);
private:
    Ui::MainView *ui;
    ClientSocket* clientSocket;
};

#endif // MAINVIEW_H
