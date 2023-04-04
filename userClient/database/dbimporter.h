#ifndef DBIMPORTER_H
#define DBIMPORTER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVector>
#include <QPair>

class DBImporter : public QSqlDatabase
{
public:
    DBImporter();
    void getList();
    QVector <QPair<QString,QString>> vector_registered;
    void closeConnection();
private:
    void connectToDB();
    QSqlDatabase db;


};

#endif // DBIMPORTER_H
