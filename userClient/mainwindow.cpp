#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_login, SIGNAL(clicked()), SLOT(press_login()));
    connectToDB();
    connect(ui->pushButton_register, SIGNAL(clicked()), SLOT(registerNewUser()));

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

void MainWindow::connectToDB()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("messager_db");
    db.setPassword("");
    db.setPort(5432);
    bool ok = db.open();
    if(!ok)
    {
        qDebug() << " Some problems with connection to Database";
        qDebug() << db.lastError();
    }
    else
        qDebug() << "Connection success";

}

void MainWindow::press_login()
{
    QString username = ui->lineEdit_nick->text();
    openChat_login(username);
}

void MainWindow::registerNewUser()
{
    registForm = new RegistrationForm();
    registForm->show();
}

