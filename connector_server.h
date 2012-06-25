#ifndef CONNECTOR_SERVER_H
#define CONNECTOR_SERVER_H

#include <QObject>


#include <QDataStream>
#include <QString>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

class Connector_Server : public QObject
{
    Q_OBJECT
private:
    QTcpServer *connected_Server;
    QString connected_str;
    quint16 NextBlockSize;

public:
    Connector_Server(int nPort);

public slots:
    void slotReadClient();
    void slotNewConnection();

signals:
    void NewOutput(QString);
};

#endif // CONNECTOR_SERVER_H
