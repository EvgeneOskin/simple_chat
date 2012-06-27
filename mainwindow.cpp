#include "mainwindow.h"

MainWindow::MainWindow()
    :QWidget()
{
    comment_label = new QLabel("It's for your reciever IP or host name");
    connection_label = new QLabel("Disconected!");
    out_label = new QLabel("It's for output");
    in_label = new QLabel("It's for  input");
    in_connection_name = new QLineEdit();
    out_text = new QTextEdit("Here you will receive messages");
    input_text = new QTextEdit();
    send_PshBttn = new QPushButton("Send");
    exit_PshBttn = new QPushButton("Exit");
    input_Layout = new QBoxLayout(QBoxLayout::TopToBottom);
    output_Layout = new QBoxLayout(QBoxLayout::TopToBottom);
    IOput_Layout = new QBoxLayout(QBoxLayout::LeftToRight);
    total_Layout = new QBoxLayout(QBoxLayout::TopToBottom);
    S_connector = new Connector_Server(2323);
    C_connector = new Connector_Client("localhost",2323);
    out_text->setReadOnly(true);

    input_Layout->addSpacing(2);
    input_Layout->addWidget(in_label, 0);
    input_Layout->addWidget(input_text, 5);
    input_Layout->addWidget(send_PshBttn, 0);
    input_Layout->addSpacing(2);

    output_Layout->addSpacing(2);
    output_Layout->addWidget(out_label, 0);
    output_Layout->addWidget(out_text, 5);
    output_Layout->addWidget(exit_PshBttn, 0);
    output_Layout->addSpacing(2);

    IOput_Layout->addSpacing(2);
    IOput_Layout->addLayout(input_Layout, 2);
    IOput_Layout->addStretch(0);
    IOput_Layout->addLayout(output_Layout, 2);
    IOput_Layout->addSpacing(2);

    total_Layout->addWidget(comment_label, 0);
    total_Layout->addWidget(in_connection_name, 0);
    total_Layout->addLayout(IOput_Layout, 2);
    total_Layout->addWidget(connection_label, 0);

    setLayout(total_Layout);

    QObject::connect(in_connection_name, SIGNAL(returnPressed()), this, SLOT(slotRead_Conection_Name()));
    QObject::connect(send_PshBttn, SIGNAL(clicked()), this, SLOT(slotReadStr()));
    QObject::connect(this, SIGNAL(NewInput_Self(QString)), C_connector, SLOT(slotSendToServer(QString)));
    QObject::connect(S_connector, SIGNAL(NewOutput(QString)), out_text, SLOT(setText(QString)));
    QObject::connect(exit_PshBttn, SIGNAL(clicked()), this, SIGNAL(close_MainWindow()));
    QObject::connect(C_connector, SIGNAL(connection_lost()), this, SLOT(slotServer_disconnected()));

    slotServer_disconnected();
}


void MainWindow::slotReadStr()
{
    QString Read_str;
    Read_str = input_text->toPlainText();
    input_text->setText("");
    emit NewInput_Self(Read_str);
}

void MainWindow::slotRead_Conection_Name()
{
    Connection_Name = in_connection_name->text();
    in_connection_name->setText("");
    C_connector->disconnect();
    delete C_connector;
    C_connector = new Connector_Client(Connection_Name,2323);
    QObject::connect(this, SIGNAL(NewInput_Self(QString)), C_connector, SLOT(slotSendToServer(QString)));
    QObject::connect(C_connector, SIGNAL(connection_lost()), this, SLOT(slotServer_disconnected()));
    QTimer::singleShot(3000, this, SLOT(slotCheckConnection()));
}

void MainWindow::slotServer_disconnected()
{
    connection_label->setText("Disconected!");
    input_text->setText("Sorry, I\'m lost connection with Server");
    input_text->setReadOnly(true);
    bool bOk;
    Connection_Name = QInputDialog::getText(this, "host name",
                                                    "Sorry, i lost current connection\nPlease input new host name (or IP):",
                                                    QLineEdit::Normal, "", &bOk);
    if(bOk)
    {
        C_connector->disconnect();
        if (C_connector->isConnectedToHost())
            delete C_connector;
        C_connector = new Connector_Client(Connection_Name,2323);
        QObject::connect(this, SIGNAL(NewInput_Self(QString)), C_connector, SLOT(slotSendToServer(QString)));
        QObject::connect(C_connector, SIGNAL(connection_lost()), this, SLOT(slotServer_disconnected()));
        QTimer::singleShot(3000, this, SLOT(slotCheckConnection()));
    }
}

void MainWindow::slotCheckConnection()
{
    if (!C_connector->isConnectedToHost())
        slotServer_disconnected();
    else
    {
        Connection_Name = "Conected to " + Connection_Name + "!";
        connection_label->setText(Connection_Name);
        Connection_Name = "";
        out_text->setText("");
        input_text->setText("");
        input_text->setReadOnly(false);
    }

}
