#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "registrationform.h"
#include "chatdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openChat_login(QString nickname);
    void connectToDB();

public slots:

    void press_login();
    void registerNewUser();


private:
    Ui::MainWindow *ui;


    ChatDialog *chat ;
    RegistrationForm *registForm;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
