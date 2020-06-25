#include "MainView.h"
#include "ui_MainView.h"
#include "File_Management.h"
#include <vector>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    Container myJson;
    vector<string> documents = myJson.listDocument();

    QStringList fileList;
    for(size_t i=0; i<documents.size(); i++)
    {
        fileList.append(documents[i].c_str());
    }

    QStringListModel fileListModel;
    fileListModel.setStringList(fileList);

    ui->listView->setModel(&fileListModel);
}

MainView::~MainView()
{
    delete ui;
    if(clientSocket != nullptr)
    {
        delete  clientSocket;
        clientSocket = nullptr;
    }
}

void MainView::setClientSocket(ClientSocket *sock)
{
    this->clientSocket = sock;
}
