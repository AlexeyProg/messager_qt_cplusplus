#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Messager");
    socket = new QTcpSocket(this);

    connect(ui->pushButton_connect, SIGNAL(clicked(bool)), this,SLOT(connectToServer()));
    connect(socket, &QTcpSocket::connected, this, &MainWindow::ReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect(ui->pushButton_send, SIGNAL(clicked(bool)), this, SLOT(slotSendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendToServer(QString str)
{
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out << str;
    socket->write(data);
    ui->lineEdit_message->clear();
}

void MainWindow::connectToServer()
{
    socket->connectToHost("127.0.0.1", 12);
    qDebug() << "connected";
}

void MainWindow::ReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_3);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        ui->textBrowser->append(str);

    }
    else
    {
        ui->textBrowser->append(ERROR);
    }
}

void MainWindow::slotSendMessage()
{
    sendToServer(ui->lineEdit_message->text());

}

