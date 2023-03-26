#include "chatdialog.h"
#include "ui_chatdialog.h"

ChatDialog::ChatDialog(QString nickname, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Messager");
    userName = nickname;
    socket = new QTcpSocket(this);


    ui->lineEdit->setEnabled(false);

    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(deleteLater()));
    connect(ui->pushButton_connect, SIGNAL(clicked()), SLOT(connectToServer()));
}

void ChatDialog::sendToServer(QString msg)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    QString current_time = QTime::currentTime().toString();
    QString full_message = current_time + "(" + userName +  ") : " + msg;
    out << full_message;
    qDebug() << current_time << "("<< userName << ") : " << msg;
    socket->write(data);
    ui->lineEdit->clear();
}

void ChatDialog::slotReadyRead()
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

void ChatDialog::connectToServer()
{
    socket->connectToHost("127.0.0.1", 1234);
    if(socket->waitForConnected(1000))
    {
        QString userConnected = userName + " connected to chat";
//        ui->textBrowser->append(userConnected);
        sendToServer(userConnected);
        ui->pushButton_connect->hide();
        ui->lineEdit->setEnabled(true);
    }
    else
    {
        ui->textBrowser->append("Connection error");
    }
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::on_pushButton_send_clicked()
{
    sendToServer(ui->lineEdit->text());
}



void ChatDialog::on_lineEdit_returnPressed()
{
    sendToServer(ui->lineEdit->text());
}

