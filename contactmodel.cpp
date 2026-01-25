#include "contactmodel.h"

// This is what Qt calls the "model", which is
// the glue between the object (or QList of objects)
// and the UI grid.

ContactModel::ContactModel(QList<Contact>& contacts, ContactWindow *parent)
    : QAbstractTableModel(parent), list_ref_in_model(contacts) {
}

int ContactModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : list_ref_in_model.size();
}

int ContactModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 2;
}

QVariant ContactModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    Contact contact = list_ref_in_model.at(index.row());
    if (index.column() == 0)
        return contact.name;
    else if (index.column() == 1)
        return contact.number;
    else return QVariant();

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

void ContactModel::addContact(const QString& name, const QString &number) {
    beginInsertRows(QModelIndex(), list_ref_in_model.size(), list_ref_in_model.size());
    list_ref_in_model.append(Contact{name, number});
    endInsertRows();
}

void ContactModel::removeContact(int row) {
    if (row >= 0 && row < list_ref_in_model.size()) {
        beginRemoveRows(QModelIndex(), row, row);
        list_ref_in_model.removeAt(row);
        endRemoveRows();
    }
}

bool ContactModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    Contact &contact = list_ref_in_model[index.row()];

    if (index.column() == 0) {
        contact.name = value.toString();
    } else if (index.column() == 1) {
        contact.number = value.toString();
    }

    emit dataChanged(index, index, {role});
    return true;
}
