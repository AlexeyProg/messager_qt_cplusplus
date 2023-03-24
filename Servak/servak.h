#ifndef SERVAK_H
#define SERVAK_H

#include <QTcpServer>
#include <QObject>
#include <QTcpSocket>
#include <QVector>
#include <QHostAddress>
#include <QDataStream>
#include <QByteArray>

class Servak : public QTcpServer
{
    Q_OBJECT
public:
    Servak();
    QTcpSocket *socket;
    void sendToUser(QString message);
    QVector<QTcpSocket*> vector_socket;
    QByteArray data;

public slots:
    void slotReadyRead();


    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle);
};

#endif // SERVAK_H
