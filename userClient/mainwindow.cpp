#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Messager");
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(deleteLater()));
    connect(ui->pushButton_connect, SIGNAL(clicked()), SLOT(connectToServer()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendToServer(QString msg)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    QString current_time = QTime::currentTime().toString();
    QString full_message = current_time + "(" + ") : " + msg;
    out << full_message;
    qDebug() << current_time << "("<< userName << ") : " << msg;
    socket->write(data);
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        ui->textBrowser->append(str);
    }
    else
    {
        ui->textBrowser->append("datastream readyread error");
    }

}

void MainWindow::connectToServer()
{
    if(ui->lineEdit_nickname->text().isEmpty())
    {
        QMessageBox::warning(this,"Login error","You need to login! Maybe your nickname field is empty");
        return;
    }
    else
    {
        userName = ui->lineEdit_nickname->text();
        socket->connectToHost("127.0.0.1", 1234);
        if(socket->waitForConnected(5000))
        {
            ui->textBrowser->append(QString(userName + " connected to chat"));
        }
        else
        {
            ui->textBrowser->append("Connection error");
        }
    }
}


void MainWindow::on_pushButton_send_clicked()
{
    sendToServer(ui->lineEdit->text());
}

