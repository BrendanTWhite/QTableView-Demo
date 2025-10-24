#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <QMainWindow>

class ContactModel;

namespace Ui {
class ContactManager;
}

class ContactManager : public QMainWindow {
    Q_OBJECT

public:
    explicit ContactManager(QWidget *parent = nullptr);
    ~ContactManager();

private slots:
    void addContact();
    void removeContact();
    void editContact();

private:
    Ui::ContactManager *ui;
    ContactModel *model;
};

#endif // CONTACTMANAGER_H
