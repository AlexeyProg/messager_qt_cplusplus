#include "dbimporter.h"

DBImporter::DBImporter()
{
    connectToDB();
}

void DBImporter::connectToDB()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setUserName("sokol");
    db.setDatabaseName("messager_db");
    db.setPassword("");
    bool ok = db.open();
    if(ok)
        qDebug() << "Connection successful";
    else
        qDebug() << "Some problems with connection to db";
}

void DBImporter::getList()
{
    vector_registered.clear();
    QSqlQuery q;
    q.exec("select username,password from Persons;");
    while(q.next())
    {
        QString u_login = q.value(0).toString();
        QString u_pass = q.value(1).toString();
        vector_registered.push_back(qMakePair(u_login,u_pass));
    }
}

void DBImporter::closeConnection()
{
    db.close();
}
