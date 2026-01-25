#ifndef CONTACT_H
#define CONTACT_H

#include <QList>
#include <QString>

class Contact
{
public:
Contact(const QString& name, const QString& number);

    QString name;
    QString number;

};

#endif // CONTACT_H
