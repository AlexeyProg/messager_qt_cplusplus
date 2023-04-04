#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Login page");
    connect(ui->pushButton_login, SIGNAL(clicked()), SLOT(press_login()));
//    connectToDB();
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

bool MainWindow::checkUserInDB(QString username, QString password)
{
    importer = new DBImporter();
    importer->getList();
    QVector<QPair<QString,QString>> v = importer->vector_registered;
    for(const auto &item : v)
    {
        if(item.first == username && item.second == password)
        {
            qDebug() << "Logging in ...";
            openChat_login(username);
            return true;
        }
    }
    return false;
}

void MainWindow::press_login()
{
    QString cur_username = ui->lineEdit_nick->text();
    QString user_pass = ui->lineEdit_password->text();
    bool logging_in = checkUserInDB(cur_username, user_pass);
    if(!logging_in)
        QMessageBox::warning(this,"Unknown user","Error!");

//    openChat_login(cur_username);
}

void MainWindow::registerNewUser()
{
    registForm = new RegistrationForm();
    registForm->show();
}

