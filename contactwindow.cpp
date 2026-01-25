#include "contactwindow.h"
#include "ui_contactwindow.h"
#include "contactmodel.h"

#include <QMessageBox>
#include <QInputDialog>

// ContactWindow is them main form, with methods for Add, Remove, and Edit

ContactWindow::ContactWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_ptr(new Ui::ContactManager),
    model_ptr_in_window(new ContactModel(this->list_in_window, this))
{
    // Set up UI
    ui_ptr->setupUi(this);
    ui_ptr->contactTableView->setModel(model_ptr_in_window);
    ui_ptr->contactTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui_ptr->contactTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    // Connect signals for buttons
    connect(ui_ptr->addButton, &QPushButton::clicked, this, &ContactWindow::addContact);
    connect(ui_ptr->removeButton, &QPushButton::clicked, this, &ContactWindow::removeContact);
    connect(ui_ptr->editButton, &QPushButton::clicked, this, &ContactWindow::editContact);
}

ContactWindow::~ContactWindow() {
    delete ui_ptr;
}

void ContactWindow::addContact() {
    QString name = ui_ptr->nameLineEdit->text();
    QString number = ui_ptr->numberLineEdit->text();
    if (!number.isEmpty() && !number.toStdString().empty() && !number.toLongLong()) {
          QMessageBox::warning(this, "Warning", "Please enter a valid number (only digits).");
          return;
      }
    if (name.isEmpty() || number.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both name and number.");
        return;
    }

    // If we got this far, then everything is good to go
    model_ptr_in_window->addContact(name, number);
    ui_ptr->nameLineEdit->clear();
    ui_ptr->numberLineEdit->clear();
}

void ContactWindow::removeContact() {
    QModelIndex index = ui_ptr->contactTableView->currentIndex();
    if (index.isValid()) {
        model_ptr_in_window->removeContact(index.row());
    } else {
        QMessageBox::warning(this, "Warning", "Please select a contact to remove.");
    }
}


void ContactWindow::editContact() {
    QModelIndex index = ui_ptr->contactTableView->currentIndex();
    if (index.isValid()) {

        QString currentName = model_ptr_in_window->data(model_ptr_in_window->index(index.row(), 0)).toString();
        QString currentNumber = model_ptr_in_window->data(model_ptr_in_window->index(index.row(), 1)).toString();


        QString name = QInputDialog::getText(this, "Edit Contact", "Enter new contact name:", QLineEdit::Normal, currentName);
        if (!name.isEmpty()) {
            QString number = QInputDialog::getText(this, "Edit Contact", "Enter new contact number:", QLineEdit::Normal, currentNumber);
            if (!number.isEmpty()) {

                model_ptr_in_window->setData(model_ptr_in_window->index(index.row(), 0), name);
                model_ptr_in_window->setData(model_ptr_in_window->index(index.row(), 1), number);
            }
        }
    } else {
        QMessageBox::warning(this, "Warning", "Please select a contact to edit.");
    }
}

