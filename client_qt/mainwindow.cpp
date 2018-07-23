#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <iostream>
#include  <sys/socket.h>
#include  <arpa/inet.h>
#include  <string.h>
#include  <netinet/in.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("OICQ"));
    QPalette palette(this->palette());
   // palette.setColor(QPalette::Background, Qt::lightGray);
    this->setPalette(palette);
    QObject::connect(ui->SendMsgEdit, SIGNAL(returnPressed()), this, SLOT(SendMsg()));
    socket =  SocketInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTcpSocket* MainWindow::SocketInit()
{
   QTcpSocket *m_socket = new QTcpSocket;
   m_socket->connectToHost("127.0.0.1", 30000, QTcpSocket::ReadWrite);
   m_socket->waitForConnected();
   return m_socket;
}

void MainWindow::SendMsg()
{
    QString str;

    str = ui->SendMsgEdit->text();
    ui->SendMsgEdit->clear();
    socket->write(str.toStdString().c_str(), str.length());
    ui->RevMsgShow->append("Send: "+str);
}
