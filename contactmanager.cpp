#include "contactmanager.h"
#include "ui_contactmanager.h"
#include "contactmodel.h"
#include <QMessageBox>
#include <QInputDialog>

ContactManager::ContactManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactManager),
    model(new ContactModel(this)) {

    ui->setupUi(this);
    ui->contactTableView->setModel(model);
    ui->contactTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->contactTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    // Connect signals for buttons
    connect(ui->addButton, &QPushButton::clicked, this, &ContactManager::addContact);
    connect(ui->removeButton, &QPushButton::clicked, this, &ContactManager::removeContact);
    connect(ui->editButton, &QPushButton::clicked, this, &ContactManager::editContact);
}

ContactManager::~ContactManager() {
    delete ui;
}

void ContactManager::addContact() {
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
    model->addContact(name, number);
    ui->nameLineEdit->clear();
    ui->numberLineEdit->clear();
}

void ContactManager::removeContact() {
    QModelIndex index = ui->contactTableView->currentIndex();
    if (index.isValid()) {
        model->removeContact(index.row());
    } else {
        QMessageBox::warning(this, "Warning", "Please select a contact to remove.");
    }
}


void ContactManager::editContact() {
    QModelIndex index = ui->contactTableView->currentIndex();
    if (index.isValid()) {

        QString currentName = model->data(model->index(index.row(), 0)).toString();
        QString currentNumber = model->data(model->index(index.row(), 1)).toString();


        QString name = QInputDialog::getText(this, "Edit Contact", "Enter new contact name:", QLineEdit::Normal, currentName);
        if (!name.isEmpty()) {
            QString number = QInputDialog::getText(this, "Edit Contact", "Enter new contact number:", QLineEdit::Normal, currentNumber);
            if (!number.isEmpty()) {

                model->setData(model->index(index.row(), 0), name);
                model->setData(model->index(index.row(), 1), number);
            }
        }
    } else {
        QMessageBox::warning(this, "Warning", "Please select a contact to edit.");
    }
}

