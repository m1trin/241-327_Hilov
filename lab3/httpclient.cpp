#include "httpclient.h"

#include <QDebug>

HttpClient *HttpClient::m_instance = nullptr;

HttpClient::HttpClient(QObject *parent)
    : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
}

HttpClient *HttpClient::getInstance()
{
    if (!m_instance) {
        m_instance = new HttpClient();
    }

    return m_instance;
}

void HttpClient::list()
{
    QNetworkRequest request{QUrl("http://localhost/api/cars/")};

    QNetworkReply *reply = m_networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "List error:" << reply->errorString();
        }

        emit dataReceived(reply->readAll());
        reply->deleteLater();
    });
}

void HttpClient::get(int id)
{
    QString url = QString("http://localhost/api/cars/%1/").arg(id);

    qDebug() << "GET:" << url;

    QNetworkRequest request{QUrl(url)};

    QNetworkReply *reply = m_networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Get error:" << reply->errorString();
        }

        emit dataReceived(reply->readAll());
        reply->deleteLater();
    });
}

void HttpClient::create(const QByteArray &data)
{
    QNetworkRequest request{QUrl("http://localhost/api/cars/")};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_networkAccessManager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Create error:" << reply->errorString();
        }

        emit dataReceived(reply->readAll());
        reply->deleteLater();
    });
}

void HttpClient::update(int id, const QByteArray &data)
{
    QString url = QString("http://localhost/api/cars/%1/").arg(id);

    qDebug() << "PUT:" << url;

    QNetworkRequest request{QUrl(url)};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_networkAccessManager->put(request, data);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Update error:" << reply->errorString();
        }

        emit dataReceived(reply->readAll());
        reply->deleteLater();
    });
}

void HttpClient::remove(int id)
{
    QString url = QString("http://localhost/api/cars/%1/").arg(id);

    qDebug() << "DELETE:" << url;

    QNetworkRequest request{QUrl(url)};

    QNetworkReply *reply = m_networkAccessManager->deleteResource(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Delete error:" << reply->errorString();
        }

        emit dataReceived(reply->readAll());
        reply->deleteLater();
    });
}

HttpClient::~HttpClient()
{
}