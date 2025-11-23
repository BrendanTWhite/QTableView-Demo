#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QList>
#include <QVariant>
#include <QBrush>

#include "contactmanager.h"


class ContactModel : public QAbstractTableModel {
    Q_OBJECT

public:

    explicit ContactModel(QObject *parent = nullptr);


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;


    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    void addContact(const QString &name, const QString &number);
    void removeContact(int row);
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

};

#endif // CONTACTMODEL_H
