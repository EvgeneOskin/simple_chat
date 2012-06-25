#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication master_application(argc, argv);
    MainWindow mwdgt;
    mwdgt.show();

//    QWidget main_widget;
//    QLabel *out_label = new QLabel("It's for output");
//    QLabel *in_label = new QLabel("It's for  input");
//    QTextEdit *out_text = new QTextEdit("Here you will see what input");
//    QPushButton *send_PshBttn = new QPushButton("Send");
//    QPushButton *exit_PshBttn = new QPushButton("Exit");
//    QBoxLayout *input_Layout = new QBoxLayout(QBoxLayout::TopToBottom);
//    QBoxLayout *output_Layout = new QBoxLayout(QBoxLayout::TopToBottom);
//    QBoxLayout *total_Layout = new QBoxLayout(QBoxLayout::LeftToRight);
//    Connector *input_text = new Connector();
//    out_text->setReadOnly(true);

//    input_Layout->addSpacing(2);
//    input_Layout->addWidget(in_label, 0);
//    input_Layout->addWidget(input_text, 10);
//    input_Layout->addWidget(send_PshBttn, 0);
//    input_Layout->addSpacing(2);
//    output_Layout->addSpacing(2);
//    output_Layout->addWidget(out_label, 0);
//    output_Layout->addWidget(out_text, 10);
//    output_Layout->addWidget(exit_PshBttn, 0);
//    output_Layout->addSpacing(2);

//    total_Layout->addSpacing(2);
//    total_Layout->addLayout(input_Layout, 2);
//    total_Layout->addStretch(0);
//    total_Layout->addLayout(output_Layout, 2);
//    total_Layout->addSpacing(2);
//    main_widget.setLayout(total_Layout);

//    main_widget.show();
//    QObject::connect(send_PshBttn, SIGNAL(clicked()), input_text, SLOT(slotReedStr()));
//    QObject::connect(input_text, SIGNAL(NewInput(QString)), out_text, SLOT(setText(QString)));
//    QObject::connect(exit_PshBttn, SIGNAL(clicked()), &master_application, SLOT(quit()));

    QObject::connect(mwdgt.send_PshBttn, SIGNAL(clicked()), mwdgt.input_text, SLOT(slotReedStr()));
    QObject::connect(mwdgt.input_text, SIGNAL(NewInput(QString)), mwdgt.out_text, SLOT(setText(QString)));
    QObject::connect(mwdgt.exit_PshBttn, SIGNAL(clicked()), &master_application, SLOT(quit()));

    return master_application.exec();
}
