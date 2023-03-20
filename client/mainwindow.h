#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define ERROR "Error!"

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray data;
    void sendToServer(QString str);

public slots:
    void connectToServer();
    void ReadyRead();
    void slotSendMessage();
};
#endif // MAINWINDOW_H