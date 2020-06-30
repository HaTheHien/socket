#include "Session.h"

//QString GetRandomString()
//{
//   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
//   const int randomStringLength = 12; // assuming you want random strings of 12 characters

//   QString randomString;
//   for(int i=0; i<randomStringLength; ++i)
//   {
//       int index = qrand() % possibleCharacters.length();
//       QChar nextChar = possibleCharacters.at(index);
//       randomString.append(nextChar);
//   }
//   return randomString;
//}

Session::Session()
{

}

void Session::StartToLogin(ClientSocket *clientSocket, QString username, QString password)
{
    this->passBySocket = clientSocket;
    this->username = username;
    this->password = password;

//    QMessageBox loginDialog;
//    loginDialog.setWindowIcon(QIcon(":/icons/origami.ico"));
//    loginDialog.setText("Logining in...\nPlease wait");
//    loginDialog.setStandardButtons(QMessageBox::StandardButton::Cancel);
//    QAbstractButton* cancelButton = loginDialog.button(QMessageBox::StandardButton::Cancel);

//    auto f = [&](){
//        Session s;
//        s.Login(clientSocket,username,password);

//        QObject::connect(&s, &Session::OnServerEcho,
//                         this, &Session::OnServerEcho);
//        QObject::connect(&s, &Session::OnLoginSuccess,
//                         this, &Session::OnLoginSuccess);
//    };
//    this->worker = QThread::create(f);

    //this->worker = QThread::create(Login, clientSocket,username,password);

//    QThread* worker = QThread::create(Login, clientSocket,username,password);

//    QObject::connect(cancelButton, &QAbstractButton::clicked,
//                     worker, &QThread::quit);

//    QObject::connect(worker, &QThread::finished,
//                     &loginDialog, &QMessageBox::hide);

    //worker->start();

    QTimer singleShot;
    singleShot.setSingleShot(true);
    QObject::connect(&singleShot, &QTimer::timeout,
                     this, &Session::Login_);
    singleShot.start();

    //loginDialog.exec();
}

void Session::Login(ClientSocket *clientSocket, QString username, QString password)
{
    if(!clientSocket->isValid())
    {
        throw std::exception("Invalid Socket Exception!");
    }

    if(username.contains(" ") || password.contains(" ") || username.isEmpty() || password.isEmpty())
    {
        throw std::exception("Invalid Username or Password!");
    }

    //<Packet size: 4 byte> <LOGIN: 4 byte> <Username> <space> <Password>
    QString dataToSend;

    QString packetSize = QString::number(4 + 4 + username.length() + 1 + password.length());
    for(int i = packetSize.length(); i < 4; i++)
    {
        packetSize = "0" + packetSize;
    }

    dataToSend += packetSize + LOGIN + username + " " + password;
    clientSocket->Send(dataToSend);

    QString feedback;
    QString anwserCode;

    //LOGIN REQUEST
    do {
        //Get login result
        clientSocket->Receive();
        /*
         * feedback message format:
         * <Packet size: 4 byte> <NOT_OK: 4 byte> <Message> or
         * <Packet size: 4 byte> <OK: 4 byte> <Version of files>
         */

        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        if(anwserCode == NOTOK)
        {
            throw std::exception("Invalid Username or Password!");
        }
        else if (anwserCode == ECHO)
        {
            //QString echo = feedback.mid(8);
            //emit OnServerEcho(echo);
            continue;
        }
        else if(anwserCode == UPDATE)
        {
            continue;
        }
        else if(anwserCode == OK)
        {
            Container myJson;
            QString version = myJson.version().c_str();

            if(version == feedback.mid(8))
            {
                dataToSend = "0008" + QString(UP_TO_DATE);
                clientSocket->Send(dataToSend);
                emit OnLoginSuccess(clientSocket);
                return;
            }
            else //Json out of date need to update
            {
                dataToSend = "0008" + QString(READY); //Ask server send last version
                clientSocket->Send(dataToSend);
                break;
            }
        }
        else
        {
            qDebug() <<"anserCode: " << anwserCode;
            throw std::exception("Login: Unknown Exception!");
        }

    } while(true);

    //UPDATE JSON FILE

    ofstream fout(PACKG); //"file.json"
    QString fileData;
    while (true)
    {
        clientSocket->Receive();
        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        if(anwserCode == FILE_)
        {
            fileData = feedback.mid(8);
            fout<<fileData.toStdString();
        }
        else if(anwserCode == END_OF_FILE)
        {
            fileData = feedback.mid(8);
            fout<<fileData.toStdString();

            dataToSend = "0008" + QString(DOWNLOAD_DONE);
            clientSocket->Send(dataToSend);

            fout.close();
            emit OnLoginSuccess(clientSocket);
            return;
        }
        else if(anwserCode == ECHO)
        {
            //QString echo = feedback.mid(8);
            //emit OnServerEcho(echo);
            continue;
        }
        else
        {
            fout.close();
            throw std::exception("Unknown Exception!");
        }

        dataToSend = "0008" + QString(ACK);
        clientSocket->Send(dataToSend);
    }

    fout.close();
    emit OnLoginSuccess(clientSocket);
    return;
}

void Session::Register(ClientSocket *clientSocket, QString username, QString password)
{
    if(!clientSocket->isValid())
    {
        throw std::exception("Invalid Socket Exception!");
    }

    if(username.contains(" ") || password.contains(" ") || username.isEmpty() || password.isEmpty())
    {
        throw std::exception("Invalid Username or Password!");
    }

    //<Packet size: 4 byte> <LOGIN: 4 byte> <Username> <space> <Password>
    QString dataToSend;

    QString packetSize = QString::number(4 + 4 + username.length() + 1 + password.length());
    for(int i = packetSize.length(); i < 4; i++)
    {
        packetSize = "0" + packetSize;
    }

    dataToSend += packetSize + RES + username + " " + password;
    clientSocket->Send(dataToSend);

    QString feedback;
    QString anwserCode;

    //REGISTER REQUEST
    do {
        //Get login result
        clientSocket->Receive();
        /*
         * feedback message format:
         * <Packet size: 4 byte> <NOT_OK: 4 byte> <Message> or
         * <Packet size: 4 byte> <OK: 4 byte> <Version of files>
         */

        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        if(anwserCode == NOTOK)
        {
            QString mess = "Invalid Username or Password!\n" + feedback.mid(8);
            throw std::exception(mess.toStdString().c_str());
        }
        else if (anwserCode == ECHO)
        {
            //QString echo = feedback.mid(8);
            //emit OnServerEcho(echo);
            continue;
        }
        else if(anwserCode == UPDATE)
        {
            continue;
        }
        else if(anwserCode == OK)
        {
            throw std::exception("Register Successfully!");
        }
        else
        {
            qDebug() <<"anserCode: " << anwserCode;
            throw std::exception("Unknown Exception!");
        }

    } while(true);
}

void Session::Upload(ClientSocket *clientSocket)
{
    if(clientSocket == nullptr)
    {
        throw std::exception("Upload: clientSocket: Null Exception!");
    }
    if(!clientSocket->isValid())
    {
        throw std::exception("Upload: Invalid Socket Exception!");
    }

    //ASK WHERE IS FILE LOCATED
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    //Get the path
    QString filePath = fileDialog.getOpenFileName();
    qDebug() << filePath;
    //Just take name
    QString filename = filePath.mid(filePath.lastIndexOf('/') + 1);
    qDebug() << filename;


    QFileInfo fileInfo(filePath);
    qint64 fileSize = fileInfo.size();

    if(fileSize > 200*1024*1024)    //Maximum upload file is 200MB
    {
        throw std::exception("Upload: Oversize!");
    }

    //<Packet size: 4byte> <UPLOAD> <File size> <space> <file name>
    QString dataToSend;

    QString packetSize = QString::number(4 + 4 + QString::number(fileSize).length() + 1 + filename.length());
    for(int i = packetSize.length(); i < 4; i++)
    {
        packetSize = "0" + packetSize;
    }

    dataToSend = packetSize + UPLOAD + QString::number(fileSize) + " " + filename;
    clientSocket->Send(dataToSend);

    QString feedback;
    QString anwserCode;
    //UPLOAD REQUEST
    while(true)
    {
        clientSocket->Receive();
        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        if(anwserCode == OK)
        {
            break;
        }
        else if(anwserCode == ECHO)
        {
//            dataToSend = "0008" + QString(ERR);
//            clientSocket->Send(dataToSend);

            QString echo = feedback.mid(8);
            emit OnServerEcho(echo);
            break;
        }
        else if(anwserCode == DUPLICATE_)
        {
            throw std::exception("Upload: Duplicate file name!");
        }
        else
        {
            qDebug() << feedback;
            throw std::exception("Upload: Unknown Exception!");
        }
    }

    //QFile fileToUpload(filePath);
    //QTextStream data(&fileToUpload);

    ifstream fin(filePath.toStdString(), ios::binary);
    char binanyData[4088];

    qint64 remaining = fileSize;

    //<Packet size: 4 byte> + <FILE_: 4 byte> + <Data> = STANDARD_PACKET_SIZE
    while(remaining > 0)
    {
        int tmp;
        if(remaining > STANDARD_PACKET_SIZE - 8)
        {
            packetSize = QString::number(STANDARD_PACKET_SIZE);
            anwserCode = FILE_;

            tmp = 4088;
        }
        else
        {
            //This is last packet
            packetSize = QString::number(remaining);
            for(int i = packetSize.length(); i < 4; i++)
            {
                packetSize = "0" + packetSize;
            }

            anwserCode = END_OF_FILE;
            tmp = remaining;
        }

        remaining -= STANDARD_PACKET_SIZE - 8;

        fin.read(binanyData, tmp);

        dataToSend = packetSize + anwserCode + QString(binanyData);
        clientSocket->Send(dataToSend);

        clientSocket->Receive();
        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        if(anwserCode == ACK)
        {
            continue;
        }
        else if(anwserCode == ECHO)
        {
            QString echo = feedback.mid(8);
            emit OnServerEcho(echo);
            continue;
        }
        else if(anwserCode == UPLOAD_DONE)
        {
            emit OnUploadFished();

            fin.close();
            return;
        }
        else
        {
            qDebug() << feedback;
            throw std::exception("Upload: Unknown Exception!");
        }
    }

    emit OnUploadFished();
    fin.close();
    //fileToUpload.close();
}

void Session::Download(ClientSocket *clientSocket, QString filename, QString savePath)
{
    //savePath = filename;

    if(clientSocket == nullptr)
    {
        throw std::exception("Download: clientSocket: Null Exception!");
    }
    if(!clientSocket->isValid())
    {
        throw std::exception("Download: Invalid Socket Exception!");
    }

    //<Packet size: 4 byte> <DOWNLOAD: 4 byte> <File name>
    QString dataToSend;

    QString packetSize = QString::number(4 + 4 + filename.length());
    for(int i = packetSize.length(); i < 4; i++)
    {
        packetSize = "0" + packetSize;
    }
    dataToSend = packetSize + DOWNLOAD + filename;

    clientSocket->Send(dataToSend);

    QString feedback;
    QString anwserCode;
    //DOWNLOAD REQUEST
    do
    {
        clientSocket->Receive();
        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        //Server anwser: <Packet size: 4 byte> <OK: 4 byte>
        if(anwserCode == OK)
        {
            dataToSend = "0008" + QString(READY);
            clientSocket->Send(dataToSend);
            break;
        }
        else if(anwserCode == ECHO)
        {
            dataToSend = "0008" + QString(ERR);
            clientSocket->Send(dataToSend);

            QString echo = feedback.mid(8);
            emit OnServerEcho(echo);
            return;
        }
        else
        {
            qDebug() << feedback;
            throw std::exception("Download: Unknown Exception!");
        }
    } while(true);

    //START TO DOWNLOAD
    ofstream fout(savePath.toStdString());
    QString fileData;
    while(true)
    {
        clientSocket->Receive();
        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        if(anwserCode == FILE_)
        {
            fileData = feedback.mid(8);
            fout<<fileData.toStdString();
        }
        else if(anwserCode == END_OF_FILE)
        {
            fileData = feedback.mid(8);
            fout<<fileData.toStdString();

            dataToSend = "0008" + QString(DOWNLOAD_DONE);
            clientSocket->Send(dataToSend);

            fout.close();
            emit OnDownloadFinished();
            return;
        }
        else if(anwserCode == ECHO)
        {

            dataToSend = "0008" + QString(RESEND);
            clientSocket->Send(dataToSend);

            QString echo = feedback.mid(8);
            emit OnServerEcho(echo);
            continue;
        }
        else
        {
            fout.close();
            throw std::exception("Download: Unknown Exception!");
        }

        dataToSend = "0008" + QString(ACK);
        clientSocket->Send(dataToSend);
    }

    fout.close();
    emit OnDownloadFinished();
    return;
}


void Session::Login_()
{
    this->Login(passBySocket,username,password);
}

void Session::echo(QString mess)
{
    qDebug() << "Emit " << mess;
    emit OnServerEcho(mess);
    emit OnServerEcho__();
}

void Session::echo_(QString message, int t)
{
    qDebug() << "Emit " << message;
    emit OnServerEcho_(message, t);
}

ClientSocket *Session::getPassBySocket()
{
    return this->passBySocket;
}

void Login(ClientSocket *clientSocket, QString username, QString password)
{
    if(!clientSocket->isValid())
    {
        throw std::exception("Invalid Socket Exception!");
    }

    if(username.contains(" ") || password.contains(" ") || username.isEmpty() || password.isEmpty())
    {
        throw std::exception("Invalid Username or Password!");
    }

    //<Packet size: 4 byte> <LOGIN: 4 byte> <Username> <space> <Password>
    QString dataToSend;

    QString packetSize = QString::number(4 + 4 + username.length() + 1 + password.length());
    for(int i = packetSize.length(); i < 4; i++)
    {
        packetSize = "0" + packetSize;
    }

    dataToSend += packetSize + LOGIN + username + " " + password;
    clientSocket->Send(dataToSend);

    QString feedback;
    QString anwserCode;

    //LOGIN REQUEST
    do {
        //Get login result
        clientSocket->Receive();
        /*
         * feedback message format:
         * <Packet size: 4 byte> <NOT_OK: 4 byte> <Message> or
         * <Packet size: 4 byte> <OK: 4 byte> <Version of files>
         */

        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        if(anwserCode == NOTOK)
        {
            throw std::exception("Invalid Username or Password!");
        }
        else if (anwserCode == ECHO)
        {
            QString echo = feedback.mid(8);
            //emit OnServerEcho(echo);
            continue;
        }
        else if(anwserCode == UPDATE)
        {
            continue;
        }
        else if(anwserCode == OK)
        {
            Container myJson;
            QString version = myJson.version().c_str();

            if(version == feedback.mid(8))
            {
                dataToSend = "0008" + QString(UP_TO_DATE);
                clientSocket->Send(dataToSend);
                //emit OnLoginSuccess(clientSocket);
                return;
            }
            else //Json out of date need to update
            {
                dataToSend = "0008" + QString(READY); //Ask server send last version
                clientSocket->Send(dataToSend);
                break;
            }
        }
        else
        {
            qDebug() <<"anserCode: " << anwserCode;
            throw std::exception("Unknown Exception!");
        }

    } while(true);

    //UPDATE JSON FILE

    ofstream fout(PACKG); //"file.json"

    QString fileData;
    while (true)
    {
        clientSocket->Receive();
        feedback = clientSocket->getBuffer().data();
        anwserCode = feedback.mid(4,4);

        if(anwserCode == FILE_)
        {
            fileData = feedback.mid(8);
            fout<<fileData.toStdString();
        }
        else if(anwserCode == END_OF_FILE)
        {
            fileData = feedback.mid(8);
            fout<<fileData.toStdString();

            dataToSend = "0008" + QString(DOWNLOAD_DONE);
            clientSocket->Send(dataToSend);
            fout.close();
            //emit OnLoginSuccess(clientSocket);
            return;
        }
        else if(anwserCode == ECHO)
        {
            QString echo = feedback.mid(8);
            //emit OnServerEcho(echo);
            continue;
        }
        else
        {
            fout.close();
            throw std::exception("Unknown Exception!");
        }

        dataToSend = "0008" + QString(ACK);
        clientSocket->Send(dataToSend);
    }

    fout.close();
    //emit OnLoginSuccess(clientSocket);
    return;
}


