#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
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

public slots:

    void press_login();


private:
    Ui::MainWindow *ui;
    ChatDialog *chat ;
};
#endif // MAINWINDOW_H
