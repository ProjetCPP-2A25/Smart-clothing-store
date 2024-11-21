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
}

void ChatGPTClient::sendRequest(const QString &message)
{
    lastMessage = message; // Store the message for retry purposes

    QString apiKey = "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"; // Replace with your Hugging Face API Key
    if (apiKey.isEmpty()) {
        qDebug() << "API Key not found!";
        return;
    }

    // Set up the Hugging Face API URL
    QUrl url("https://api-inference.huggingface.co/models/gpt2"); // Replace with the desired model endpoint
    QNetworkRequest request(url);

    // Add required headers
    request.setRawHeader("Authorization", "Bearer " + apiKey.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Prepare the JSON payload
    QJsonObject payload;
    payload["inputs"] = message; // The prompt or input text

    // Fixing the parameters section syntax
    QJsonObject parameters;
    parameters["max_length"] = 30;  // Increase max length
    parameters["temperature"] = 0.1; // Adjust temperature for more randomness
    //parameters["top_p"] = 1.0;      // Full diversity
    //parameters["top_k"] = 50;       // Limit the number of possible tokens

    payload["parameters"] = parameters;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    // Send the POST request
    manager->post(request, data);
}

void ChatGPTClient::onFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        // Handle rate-limiting or other errors
        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 429) {
            qDebug() << "Rate limit hit. Retrying after 1 second...";
            QTimer::singleShot(1000, this, [=] { sendRequest(lastMessage); });
        } else {
            qDebug() << "Error code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        }
        reply->deleteLater();
        return;
    }

    // Log the full response for debugging
    QByteArray response = reply->readAll();
    qDebug() << "Full Response: " << response;

    // Parse the JSON response if necessary
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    if (jsonResponse.isArray()) {
        QJsonArray jsonArray = jsonResponse.array();
        if (!jsonArray.isEmpty()) {
            QString responseText = jsonArray[0].toObject()["generated_text"].toString(); // Adjust based on your API response structure
            emit responseReceived(responseText); // Emit the parsed response
        }
    } else {
        qWarning() << "Unexpected JSON response format";
    }

    reply->deleteLater();
}
