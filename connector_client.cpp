#include "connector_client.h"

Connector_Client::Connector_Client(const QString &Host_Name, int nPort)
    :QObject(), connect_INDEX(false)
{
    connected_Socket = new QTcpSocket(this);
    connected_Socket->connectToHost(Host_Name,nPort);
    connect(connected_Socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(connected_Socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
}

Connector_Client::~Connector_Client()
{
    qDebug() << "destructor " << connect_INDEX;
    if (connect_INDEX)
        delete connected_Socket;
}

void Connector_Client::slotSendToServer(QString send_str)
{
    QByteArray Send_Block;
    QDataStream Send_stream(&Send_Block, QIODevice::WriteOnly);
    Send_stream.setVersion(QDataStream::Qt_4_8);
    Send_stream << quint16(0) << send_str;

    Send_stream.device()->seek(0);
    Send_stream << quint16(Send_Block.size() - sizeof(quint16));

    connected_Socket->write(Send_Block);
}

void Connector_Client::slotConnected()
{
    connect_INDEX = true;
}

void Connector_Client::slotDisconnected()
{
    connect_INDEX = false;
    emit connection_lost();
}

bool Connector_Client::isConnectedToHost()
{
    return connect_INDEX;
}
