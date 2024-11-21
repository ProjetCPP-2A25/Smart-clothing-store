#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class Contact {
private:
    int supplierId;
    QString contractDate;
    double price;
    int quantityImported;

public:
    // Constructors
    Contact();
    Contact(int supplierId, QString contractDate, double price, int quantityImported);

    // Getters
    int getSupplierId() const;
    QString getContractDate() const;
    double getPrice() const;
    int getQuantityImported() const;

    // Setters
    void setSupplierId(int supplierId);
    void setContractDate(QString contractDate);
    void setPrice(double price);
    void setQuantityImported(int quantityImported);
};

#endif // CONTACT_H
