#include "connector_server.h"


Connector_Server::Connector_Server(int nPort)
    : QObject(), connected_str(), NextBlockSize(0)
{
    connected_Server = new QTcpServer(this);
    if (!connected_Server->listen(QHostAddress::Any, nPort))
    {
        QMessageBox::critical(0, "Server Error",
                              "Enable ot start the server:"
                              +connected_Server->errorString());
        connected_Server->close();
        return;
    }
    connect(connected_Server,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    qDebug() << connected_Server->serverAddress();
}

void Connector_Server::slotNewConnection()
{
    static unsigned int numbersOfConnections;
    QTcpSocket *connected_ClientSocket = connected_Server->nextPendingConnection();
//  connect(connected_ClientSocket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(connected_ClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    numbersOfConnections++;
    qDebug() << "You have new connection! Server" << numbersOfConnections;
}

void Connector_Server::slotReadClient()
{

    QTcpSocket *connected_ClientSocket = (QTcpSocket*)sender();
    QDataStream Read_stream(connected_ClientSocket);
    Read_stream.setVersion(QDataStream::Qt_4_8);
    connected_str.clear();

    for(;;)
    {
        if (!NextBlockSize)
        {
            if (connected_ClientSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
        Read_stream >> NextBlockSize;
        }

        if (connected_ClientSocket->bytesAvailable() <= NextBlockSize)
        {
            break;
        }
    }

    Read_stream >> connected_str;

    emit NewOutput(connected_str);

    NextBlockSize = 0;
}
