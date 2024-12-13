#include "arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

Arduino::Arduino() {
    serial = new QSerialPort;
    arduino_port_name = "";  // Assurez-vous que ce champ est vide au départ
    arduino_is_available = false;

    // Rechercher le port série sans vérifier les identifiants
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        arduino_port_name = info.portName(); // Prenez le premier port disponible
        arduino_is_available = true;
        break; // Prenez juste un port, le premier disponible
    }
}


int Arduino::connect_arduino() {
    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        if (serial->open(QIODevice::ReadWrite)) {
            qDebug() << "Connexion à Arduino réussie sur le port" << arduino_port_name;
            return 0;  // Succès
        } else {
            qDebug() << "Erreur : impossible de se connecter à Arduino.";
            return 1;  // Échec
        }
    } else {
        qDebug() << "Erreur : Arduino non disponible.";
        return -1;  // Arduino non trouvé
    }
}


int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Connexion à Arduino fermée.";
        return 0;  // Succès
    }
    return 1;  // Échec si le port n'était pas ouvert
}
void Arduino::write_to_arduino(QByteArray data) {
    if (serial->isWritable()) {
        serial->write(data);
        qDebug() << "Données envoyées à Arduino:" << data;
    } else {
        qDebug() << "Erreur : impossible d'écrire sur le port série.";
    }
}
QByteArray Arduino::read_from_arduino() {
    if (serial->isReadable()) {
        data = serial->readAll();
        qDebug() << "Données reçues d'Arduino:" << data;
        return data;
    }
    return QByteArray();  // Retourne un tableau vide si le port n'est pas lisible
}
QSerialPort* Arduino::getserial() {
    return serial;
}
QString Arduino::getarduino_port_name() {
    return arduino_port_name;
}
