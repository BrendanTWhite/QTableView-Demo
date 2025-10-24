#include "contactmodel.h"

ContactModel::ContactModel(QObject *parent)
    : QAbstractTableModel(parent) {}

int ContactModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : contacts.size();
}

int ContactModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 2;
}

QVariant ContactModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    const Contact &contact = contacts.at(index.row());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
            return contact.name;
        else if (index.column() == 1)
            return contact.number;
    }

    return QVariant();
}

QVariant ContactModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return (section == 0) ? "Contact Name" : "Contact Number";
    } else {
        return QString::number(section + 1);
    }
}

void ContactModel::addContact(const QString &name, const QString &number) {
    beginInsertRows(QModelIndex(), contacts.size(), contacts.size());
    contacts.append({name, number});
    endInsertRows();
}

void ContactModel::removeContact(int row) {
    if (row >= 0 && row < contacts.size()) {
        beginRemoveRows(QModelIndex(), row, row);
        contacts.removeAt(row);
        endRemoveRows();
    }
}

bool ContactModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::EditRole)
        return 0;

    Contact &contact = contacts[index.row()];

    if (index.column() == 0) {
        contact.name = value.toString();
    } else if (index.column() == 1) {
        contact.number = value.toString();
    }

    emit dataChanged(index, index, {role});
}
