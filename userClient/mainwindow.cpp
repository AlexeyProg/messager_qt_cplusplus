#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_login, SIGNAL(clicked()), SLOT(press_login()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openChat_login(QString nickname)
{
    chat = new ChatDialog(nickname);
    this->close();
    chat->exec();
}

void MainWindow::press_login()
{
    QString username = ui->lineEdit_nick->text();
    openChat_login(username);
}

