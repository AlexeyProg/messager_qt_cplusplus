#ifndef PERSONCLASS_H
#define PERSONCLASS_H

#include <QObject>

class PersonClass
{
public:
    PersonClass(QString name, QString pass, int mAge);

    QString showname() const
    {
        return username;
    };
    QString showpass() const
    {
        return password;
    };
    int showAge() const
    {
        return age;
    };

private:
    QString username;
    QString password;
    int age;
};

#endif // PERSONCLASS_H
