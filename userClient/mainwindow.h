#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QVector>
#include <QDataStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QByteArray data;
    QTcpSocket *socket;
    void sendToServer(QString msg);
    QVector<QTcpSocket*> socket_vector;

public slots:
    void slotReadyRead();
    void connectToServer();



private slots:
    void on_pushButton_send_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
