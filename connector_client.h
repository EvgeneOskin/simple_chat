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
    QTcpSocket *connected_Socket;

public:
    Connector_Client(const QString &Host_Name, int nPort);

signals:
    void connection_lost();

public slots:
    void slotSendToServer(QString);
    void slotConnected();
};

#endif // CONNECTOR_CLIENT_H
