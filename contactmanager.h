#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <QMainWindow>
#include <QList>

class ContactModel; // forward declaration, to allow ptrs & refs

namespace Ui {
    class ContactManager; // change to window???
}

class ContactWindow : public QMainWindow {
    Q_OBJECT

public:

    struct Contact {  // why here? Not in contactmodel?
        QString name;
        QString number;
    };

    explicit ContactWindow(QWidget *parent = nullptr);
    ~ContactWindow();

    QList<Contact> getContacts() const; // not used
    void setContacts(const QList<Contact> &newContacts); // not used

private slots:
    void addContact();
    void removeContact();
    void editContact();

private:
    Ui::ContactManager* ui_ptr;
    ContactModel* model_ptr_in_window;

private:
    QList<Contact> list_in_window;
    // Window has actual list
};

#endif // CONTACTMANAGER_H
