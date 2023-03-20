#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();


private:
    QTcpSocket *socket;
    QByteArray data;
    QVector<QTcpSocket*> socket_vector;
    void sendToClient(QString mes);
public slots:
    void slotReadyRead();
    void incommingConnection(qintptr socketDescriptor);
    void closeApp();
};

#endif // SERVER_H
