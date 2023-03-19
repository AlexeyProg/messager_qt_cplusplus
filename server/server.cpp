#include "server.h"
#include <QDebug>

Server::Server()
{
    if(this->listen(QHostAddress::Any,12))
        qDebug() << "Listening port is "<< this->serverPort();
}

void Server::sendToClient(QString mes)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out << mes;
    socket->write(data);

}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*) sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_3);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "In status : ok";
        QString str ;
        in >> str;
        qDebug() << str;
    }
    else
    {
        qDebug() << "In status : error";
    }

}

void Server::incommingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);

    socket_vector.push_back(socket);
    qDebug() << "New client!" << " Descriptor is " << socketDescriptor;
}
