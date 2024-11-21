#ifndef CHATGPTCLIENT_H
#define CHATGPTCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer> // For handling retry logic

class ChatGPTClient : public QObject
{
    Q_OBJECT

public:
    explicit ChatGPTClient(QObject *parent = nullptr);
    void sendRequest(const QString &message);

signals:
    void responseReceived(const QString &response); // Signal to emit the response text

private slots:
    void onFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QString lastMessage; // Store the last message for retries
};

#endif // CHATGPTCLIENT_H
