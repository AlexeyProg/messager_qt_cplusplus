#include "dbexporter.h"
#include <QDebug>
#include <QSqlError>

DBExporter::DBExporter()
{
    connectToDB();
}

void DBExporter::connectToDB()
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

bool DBExporter::exportInfo(QString name, QString pass,int age)
{
    QSqlQuery query;
    QString mAge = QString::number(age);
    bool permission = checkDuplicates(name);
    if(permission)
    {
        QString request = QString("INSERT INTO PERSONS (username,password,age) "
                                  "values ('%1', '%2', '%3');").arg(name,pass,mAge);

        if(query.exec(request))
        {
            qDebug() << "Succesful create new note in Database";
            closeConnection();
        }
        else
        {
            qDebug() << "Some problems with creating new note in database";
            return false;
        }
    }
    else
        return false;
    return true;
}

void DBExporter::closeConnection()
{
    db.close();
}

bool DBExporter::checkDuplicates(QString name)
{
    QSqlQuery q;
    q.exec(QString("SELECT * FROM PERSONS WHERE username = '%1'").arg(name));
    if(q.next())
    {
        int count = q.value(0).toInt();
        if(count > 0)
        {
            qDebug() << "Duplicate username!";
            return false;
        }
    }
    return true;
}
