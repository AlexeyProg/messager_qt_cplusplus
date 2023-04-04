#ifndef DBEXPORTER_H
#define DBEXPORTER_H

#include <QSqlQuery>
#include <QSqlDatabase>

class DBExporter : public QSqlDatabase
{
public:
    DBExporter();
    void connectToDB();
    bool exportInfo(QString name, QString pass, int age);
    void closeConnection();

private:
    QSqlDatabase db;
    bool checkDuplicates(QString name);
};

#endif // DBEXPORTER_H
