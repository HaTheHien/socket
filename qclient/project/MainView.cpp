#include "MainView.h"
#include "ui_MainView.h"
//#include "File_Management.h"
#include <vector>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    this->downloadQueue = new DownloadQueue(ui->downloadQueueTab);

    Container myJson;
    vector<string> documents = myJson.listDocument();

    QStringList fileList;
    for(size_t i=0; i<documents.size(); i++)
    {
        fileList.append(documents[i].c_str());
    }

    fileList.sort();
    fileListModel.setStringList(fileList);

    ui->listView->setModel(&fileListModel);

    ui->listView->setViewMode(QListView::ViewMode::ListMode);
    ui->listView->setFlow(QListView::Flow::TopToBottom);
    ui->listView->setMovement(QListView::Movement::Free);

    ui->listView->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->listView->setSelectionMode(QListView::SelectionMode::SingleSelection);
    ui->listView->setDragDropMode(QListView::DragDropMode::NoDragDrop);

    ui->listView->setFont(QFont("Montserrat", 14));
    ui->listView->setSpacing(2);

    ui->label->hide();

    QObject::connect(ui->downloadButton, &QPushButton::clicked,
                     this, &MainView::OnDownLoadButtonClicked);
    QObject::connect(ui->uploadButton, &QPushButton::clicked,
                     this, &MainView::OnUpLoadButtonClicked);
}

MainView::~MainView()
{
    delete ui;
    if(clientSocket != nullptr)
    {
        delete  clientSocket;
        clientSocket = nullptr;
    }

    if(this->downloadQueue != nullptr)
    {
        delete this->downloadQueue;
        this->downloadQueue = nullptr;
    }
}

void MainView::setClientSocket(ClientSocket *sock)
{
    this->clientSocket = sock;
}

ClientSocket *MainView::getClientSocket()
{
    return this->clientSocket;
}

void MainView::updateListView(QStringList& newFileList)
{
    QStringList fileList = newFileList;
    this->fileListModel.setStringList(fileList);
}

QModelIndex MainView::getCurrentIndex()
{
    return ui->listView->selectionModel()->currentIndex();
}

void MainView::OnDownLoadButtonClicked()
{
    qDebug() << "Download button clicked!";
    try
    {
        QModelIndex index = this->getCurrentIndex();
        if(!index.isValid())
        {
            return;
        }

        QString fileToDownload = index.data().toString();
        //qDebug() << fileToDownload;

        Session mySession;

//        QObject::connect(&mySession, &Session::OnServerEcho,
//                         ui->label, &QLabel::setText);
//        QObject::connect(&mySession, &Session::OnServerEcho__,
//                         ui->label, &QLabel::show);
//        QObject::connect(&mySession, &Session::OnServerEcho__,
//                         ui->label, &QLabel::hide);

        auto f = [&](QString mess){
            ui->label->setText(mess);
            ui->label->show();
        };
        QObject::connect(&mySession, &Session::OnServerEcho, f);

        QString savePath = QFileDialog::getSaveFileName(this, "Save as", fileToDownload);
        if(savePath.indexOf('.') == -1) //Not found extension
        {
            savePath += ".txt";
        }
        mySession.Download(this->clientSocket, fileToDownload, savePath);
    }
    catch(std::exception& e)
    {
        QMessageBox errMess;
        errMess.setWindowIcon(QIcon(":/icons/origami.ico"));
        errMess.setWindowTitle("Info");
        errMess.setText(e.what());
        errMess.setIcon(QMessageBox::Icon::Information);
        errMess.exec();
    }
}

void MainView::OnUpLoadButtonClicked()
{
    qDebug() << "Upload button clicked!";
    try
    {
        Session mySession;

        auto f = [&](QString mess){
            ui->label->setText(mess);
            ui->label->show();
            QTimer::singleShot(2000, ui->label, &QLabel::hide);
        };
        QObject::connect(&mySession, &Session::OnServerEcho,
                         f);

        mySession.Upload(this->clientSocket);
    }
    catch(std::exception& e)
    {
        QMessageBox errMess;
        errMess.setWindowIcon(QIcon(":/icons/origami.ico"));
        errMess.setWindowTitle("Info");
        errMess.setText(e.what());
        errMess.setIcon(QMessageBox::Icon::Information);
        errMess.exec();
    }
}

void MainView::InitFileListFromJson()
{
    Container myJson;
    vector<string> documents = myJson.listDocument();

    QStringList fileList;
    for(size_t i=0; i<documents.size(); i++)
    {
        fileList.append(documents[i].c_str());
    }

    fileList.sort();
    fileListModel.setStringList(fileList);
}

void MainView::UpdateFileList(QString filename)
{

}


