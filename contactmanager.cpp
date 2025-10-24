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


    this->setStyleSheet("background-color: #f5f5f5;");


    ui->nameLineEdit->setStyleSheet(
        "QLineEdit {"
        "   background-color: #e8f0fe;"
        "   border: 1px solid #90a4ae;"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "   font-size: 14px;"
        "}"
    );

    ui->numberLineEdit->setStyleSheet(
        "QLineEdit {"
        "   background-color: #e8f0fe;"
        "   border: 1px solid #90a4ae;"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "   font-size: 14px;"
        "}"
    );

    // Styling the Add and Remove buttons
    ui->addButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #50C878;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 15px;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #009E60;"
        "}"
    );

    ui->removeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #ef5350;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 15px;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d32f2f;"
        "}"
    );

    ui->editButton->setStyleSheet(
                "QPushButton {"
                "   background-color: #42a5f5;"
                "   color: white;"
                "   border: none;"
                "   border-radius: 8px;"
                "   padding: 8px 15px;"
                "   font-size: 14px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #1e88e5;"
                "}"
            );

    // Styling the QTableView
    ui->contactTableView->setStyleSheet(
        "QTableView {"
        "   background-color: white;"
        "   alternate-background-color: #f1f8e9;"
        "   selection-background-color: #a5d6a7;"
        "   border: 1px solid #cfd8dc;"
        "   font-size: 14px;"
        "}"
        "QHeaderView::section {"
        "   background-color: #b0bec5;"
        "   color: white;"
        "   font-weight: bold;"
        "   padding: 5px;"
        "   border: 1px solid #90a4ae;"
        "}"
    );

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
    if (!name.isEmpty() && !number.isEmpty()) {
        model->addContact(name, number);
        ui->nameLineEdit->clear();
        ui->numberLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Warning", "Please enter both name and number.");
    }
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

