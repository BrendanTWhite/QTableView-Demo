#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <QMainWindow>
#include <QList>

class ContactModel;

namespace Ui {
class ContactManager;
}

class ContactManager : public QMainWindow {
    Q_OBJECT

public:

    struct Contact {
        QString name;
        QString number;
    };

    explicit ContactManager(QWidget *parent = nullptr);
    ~ContactManager();

private slots:
    void addContact();
    void removeContact();
    void editContact();

private:
    Ui::ContactManager *ui;
    ContactModel *model;

private:
    QList<Contact> contacts;
};

#endif // CONTACTMANAGER_H
