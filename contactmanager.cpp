#include "contactmanager.h"
#include <QSqlQuery>
#include <QSqlError>

bool ContactManager::addContact(const Contact& contact) {
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (supplierId, contractDate, price, quantityImported) "
                  "VALUES (:supplierId, :contractDate, :price, :quantityImported)");
    query.bindValue(":supplierId", contact.getSupplierId());
    query.bindValue(":contractDate", contact.getContractDate());
    query.bindValue(":price", contact.getPrice());
    query.bindValue(":quantityImported", contact.getQuantityImported());

    if (!query.exec()) {
        qDebug() << "Error adding contact: " << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* ContactManager::displayContacts() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT supplierId, contractDate, price, quantityImported FROM contacts");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Supplier ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Contract Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity Imported"));

    return model;
}

bool ContactManager::updateContact(const Contact& contact) {
    QSqlQuery query;
    query.prepare("UPDATE contacts SET contractDate = :contractDate, price = :price, "
                  "quantityImported = :quantityImported WHERE supplierId = :supplierId");
    query.bindValue(":supplierId", contact.getSupplierId());
    query.bindValue(":contractDate", contact.getContractDate());
    query.bindValue(":price", contact.getPrice());
    query.bindValue(":quantityImported", contact.getQuantityImported());

    return query.exec();
}

bool ContactManager::deleteContact(int supplierId) {
    QSqlQuery query;
    query.prepare("DELETE FROM contacts WHERE supplierId = :supplierId");
    query.bindValue(":supplierId", supplierId);
    return query.exec();
}
