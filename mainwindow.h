#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QTextEdit>
#include <QString>
#include "connector_client.h"
#include "connector_server.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QLabel *comment_label;
    QLabel *out_label;
    QLabel *in_label;
    QLineEdit *in_connection_name;
    QTextEdit *out_text;
    QTextEdit *input_text;
    QPushButton *send_PshBttn;
    QPushButton *exit_PshBttn;
    QBoxLayout *input_Layout;
    QBoxLayout *output_Layout;
    QBoxLayout *IOput_Layout;
    QBoxLayout *total_Layout;
    Connector_Server *S_connector;
    Connector_Client *C_connector;

public:
    MainWindow();

public slots:
    void slotReadStr();
    void slotRead_Conection_Name();

signals:
    void close_MainWindow();
    void NewInput_Self(QString);
};

#endif // MAINWINDOW_H
