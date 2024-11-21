#include "contact.h"

Contact::Contact() : supplierId(0), price(0.0), quantityImported(0) {}

Contact::Contact(int supplierId, QString contractDate, double price, int quantityImported)
    : supplierId(supplierId), contractDate(contractDate), price(price), quantityImported(quantityImported) {}

int Contact::getSupplierId() const { return supplierId; }
QString Contact::getContractDate() const { return contractDate; }
double Contact::getPrice() const { return price; }
int Contact::getQuantityImported() const { return quantityImported; }

void Contact::setSupplierId(int supplierId) { this->supplierId = supplierId; }
void Contact::setContractDate(QString contractDate) { this->contractDate = contractDate; }
void Contact::setPrice(double price) { this->price = price; }
void Contact::setQuantityImported(int quantityImported) { this->quantityImported = quantityImported; }
