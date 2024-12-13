#include "chatgptclient.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>
#include <QTimer>

ChatGPTClient::ChatGPTClient(QObject *parent)
    : QObject(parent),
      manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &ChatGPTClient::onFinished);

    predefinedResponses.insert("hi", "hello can I assist you with something?");
    predefinedResponses.insert("what is the best supplier?","Zara is the best supplier");
    predefinedResponses.insert("what is the best eco supplier?","H&M is the best eco supplier");
    predefinedResponses.insert("what is the worst supplier?","Pull&Bear is the worst supplier");
    predefinedResponses.insert("how are you?","I am great thank you");
    predefinedResponses.insert("what is the best mark?","Urban Elegance of course :)");

}

void ChatGPTClient::sendRequest(const QString &message)
{
    lastMessage = message;

    // Check for predefined responses
    if (predefinedResponses.contains(message.toLower())) {
        emit responseReceived(predefinedResponses.value(message.toLower()));
        return; // Return early if a predefined response is found
    }

    QString apiKey = "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"; // Replace with your Hugging Face API Key
    if (apiKey.isEmpty()) {
        qDebug() << "API Key not found!";
        return;
    }

    QUrl url("https://api-inference.huggingface.co/models/gpt2");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + apiKey.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject payload;
    payload["inputs"] = message;

    QJsonObject parameters;
    parameters["max_length"] = 30;
    parameters["temperature"] = 0.1;

    payload["parameters"] = parameters;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    manager->post(request, data);
}

void ChatGPTClient::onFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 429) {
            qDebug() << "Rate limit hit. Retrying after 1 second...";
            QTimer::singleShot(1000, this, [=] { sendRequest(lastMessage); });
        } else {
            qDebug() << "Error code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        }
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();
    qDebug() << "Full Response: " << response;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    if (jsonResponse.isArray()) {
        QJsonArray jsonArray = jsonResponse.array();
        if (!jsonArray.isEmpty()) {
            QString responseText = jsonArray[0].toObject()["generated_text"].toString();
            emit responseReceived(responseText);
        }
    } else {
        qWarning() << "Unexpected JSON response format";
    }

    reply->deleteLater();
}
