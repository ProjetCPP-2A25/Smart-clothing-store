#ifndef CHATGPTCLIENT_H
#define CHATGPTCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QMap> // Include QMap for predefined questions

class ChatGPTClient : public QObject
{
    Q_OBJECT

public:
    explicit ChatGPTClient(QObject *parent = nullptr);
    void sendRequest(const QString &message);

signals:
    void responseReceived(const QString &response);

private slots:
    void onFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QString lastMessage;
    QMap<QString, QString> predefinedResponses; // Map for predefined questions and answers
};

#endif // CHATGPTCLIENT_H
