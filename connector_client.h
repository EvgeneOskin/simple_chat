#ifndef CONNECTOR_CLIENT_H
#define CONNECTOR_CLIENT_H

#include <QObject>

#include <QtNetwork>
#include <QString>
#include <QTcpSocket>

class Connector_Client : public QObject
{
    Q_OBJECT
private:
    bool connect_INDEX;
    QTcpSocket *connected_Socket;

public:
    Connector_Client(const QString &Host_Name, int nPort);
    ~Connector_Client();
    bool isConnectedToHost();

signals:
    void connection_lost();

public slots:
    void slotSendToServer(QString);
    void slotConnected();
    void slotDisconnected();
};

#endif // CONNECTOR_CLIENT_H
