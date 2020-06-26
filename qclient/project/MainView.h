#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "ClientSocket.h"
#include <QStringList>
#include <QString>
#include <QStringListModel>
#include "DownloadQueue.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Session.h"

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
    ClientSocket* getClientSocket();
    void updateListView(QStringList& newFileList);
    QModelIndex getCurrentIndex();
    void InitFileListFromJson();

private:
    Ui::MainView *ui;
    ClientSocket* clientSocket = nullptr;
    QStringListModel fileListModel;
    DownloadQueue* downloadQueue;

    void OnDownLoadButtonClicked();
    void OnUpLoadButtonClicked();

signals:
    void OnServerEcho(QString& mess);
};

#endif // MAINVIEW_H
