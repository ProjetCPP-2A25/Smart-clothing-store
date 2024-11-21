#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <QSqlQueryModel>
#include "contact.h"

class ContactManager {
public:
    bool addContact(const Contact& contact);
    QSqlQueryModel* displayContacts();
    bool updateContact(const Contact& contact);
    bool deleteContact(int supplierId); // Assuming you want to delete by supplier ID
};

#endif // CONTACTMANAGER_H
