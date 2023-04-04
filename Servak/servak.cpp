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
        QString message;
        in >> message;
        qDebug() << message;
        sendToUser(message);
    }
    else
        qDebug() << "datastream error";

}

void Servak::incomingConnection(qintptr handle)
{
    socket = new QTcpSocket;
    if(socket->setSocketDescriptor(handle))
    {
        connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(slotDisconnected()));
        vector_socket.push_back(socket);
        qDebug() << " New connection! Socket Descriptor is " << handle;
    }
    else
        delete socket;
}

void Servak::slotDisconnected()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->deleteLater();
    vector_socket.removeOne(socket);
    qDebug() << "Client disconnected. Socket descriptor: " << socket->socketDescriptor();
}

