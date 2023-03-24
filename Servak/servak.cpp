#include "servak.h"

Servak::Servak()
{
    if(this->listen(QHostAddress::Any, 1234))
        qDebug() << "Listening port is " << this->serverPort();
    else
        qDebug() << "Error listening";
}

void Servak::sendToUser(QString message)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << message;
    for(QTcpSocket* item : vector_socket)
    {
        item->write(data);
    }
}

void Servak::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        qDebug() << str;
        sendToUser(str);
    }
    else
        qDebug() << "datastream error";

}

void Servak::incomingConnection(qintptr handle)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(handle);
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(deleteLater()));
    vector_socket.push_back(socket);
    qDebug() << " New connection ";
}
