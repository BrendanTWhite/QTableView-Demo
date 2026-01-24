#include "contactmanager.h"
#include "ui_contactmanager.h"
#include "contactmodel.h"

#include <QMessageBox>
#include <QInputDialog>

// ContactWindow is them main form, with methods for Add, Remove, and Edit

ContactWindow::ContactWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactManager),
    ptr_in_window(new ContactModel(this->list_in_window, this)) {

    ui->setupUi(this);
    ui->contactTableView->setModel(ptr_in_window);
    ui->contactTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->contactTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    // Connect signals for buttons
    connect(ui->addButton, &QPushButton::clicked, this, &ContactWindow::addContact);
    connect(ui->removeButton, &QPushButton::clicked, this, &ContactWindow::removeContact);
    connect(ui->editButton, &QPushButton::clicked, this, &ContactWindow::editContact);
}

ContactWindow::~ContactWindow() {
    delete ui;
}

void ContactWindow::addContact() {
    QString name = ui->nameLineEdit->text();
    QString number = ui->numberLineEdit->text();
    if (!number.isEmpty() && !number.toStdString().empty() && !number.toLongLong()) {
          QMessageBox::warning(this, "Warning", "Please enter a valid number (only digits).");
          return;
      }
    if (name.isEmpty() || number.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both name and number.");
        return;
    }

    // If we got this far, then everything is good to go
    ptr_in_window->addContact(name, number);
    ui->nameLineEdit->clear();
    ui->numberLineEdit->clear();
}

void ContactWindow::removeContact() {
    QModelIndex index = ui->contactTableView->currentIndex();
    if (index.isValid()) {
        ptr_in_window->removeContact(index.row());
    } else {
        QMessageBox::warning(this, "Warning", "Please select a contact to remove.");
    }
}


void ContactWindow::editContact() {
    QModelIndex index = ui->contactTableView->currentIndex();
    if (index.isValid()) {

        QString currentName = ptr_in_window->data(ptr_in_window->index(index.row(), 0)).toString();
        QString currentNumber = ptr_in_window->data(ptr_in_window->index(index.row(), 1)).toString();


        QString name = QInputDialog::getText(this, "Edit Contact", "Enter new contact name:", QLineEdit::Normal, currentName);
        if (!name.isEmpty()) {
            QString number = QInputDialog::getText(this, "Edit Contact", "Enter new contact number:", QLineEdit::Normal, currentNumber);
            if (!number.isEmpty()) {

                ptr_in_window->setData(ptr_in_window->index(index.row(), 0), name);
                ptr_in_window->setData(ptr_in_window->index(index.row(), 1), number);
            }
        }
    } else {
        QMessageBox::warning(this, "Warning", "Please select a contact to edit.");
    }
}

