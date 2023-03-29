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
//    socket->setProperty("username",userName);

    ui->lineEdit->setEnabled(false);

    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(deleteLater()));
    connect(ui->pushButton_connect, SIGNAL(clicked()), SLOT(connectToServer()));
}

void ChatDialog::sendToServer(QString msg)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    QString full_message = QTime::currentTime().toString() + "(" + userName +  ") : " + msg;
    out << full_message << userName;
    socket->write(data);
    ui->lineEdit->clear();
}

void ChatDialog::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok)
    {
        QString message;
        QString user;
        in >> message;
        in >> user;
        ui->textBrowser->append(message);
    }
    else
    {
        ui->textBrowser->append("datastream readyread error");
    }
    if (socket->state() == QAbstractSocket::UnconnectedState)
    {
        // Удаляем сокет из вектора сокетов
        socket_vector.removeOne(socket);

        // Удаляем объект сокета
        socket->deleteLater();
    }

}

void ChatDialog::connectToServer()
{
    socket->connectToHost("127.0.0.1", 1234);
    if(socket->waitForConnected(1000))
    {
        QString userConnected = userName + " connected to chat";
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
    QString message = ui->lineEdit->text();
    if(message.isEmpty())
    {
        QMessageBox::warning(this, "Error!", "The message is empty");
        return;
    }
    else
        sendToServer(message);
}



void ChatDialog::on_lineEdit_returnPressed()
{
    QString message = ui->lineEdit->text();
    sendToServer(message);
}

