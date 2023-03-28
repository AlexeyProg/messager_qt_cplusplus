#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QVector>
#include <QDataStream>
#include <QTime>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class ChatDialog; }
QT_END_NAMESPACE


class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QString nickname ,QWidget *parent = nullptr);
    ~ChatDialog();
    QByteArray data;
    QTcpSocket *socket;
    void sendToServer(QString msg);
    QVector<QTcpSocket*> socket_vector;

public slots:
    void slotReadyRead();
    void connectToServer();

private slots:
    void on_pushButton_send_clicked();

    void on_lineEdit_returnPressed();

private:
    QString userName;
    QByteArray nickData;

    Ui::ChatDialog *ui;
};

#endif // CHATDIALOG_H
