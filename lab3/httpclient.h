#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QByteArray>

class HttpClient : public QObject
{
    Q_OBJECT

public:
    HttpClient &operator=(HttpClient &arg) = delete;

    static HttpClient *getInstance();
    ~HttpClient();

    void list();
    void get(int id);
    void create(const QByteArray &data);
    void update(int id, const QByteArray &data);
    void remove(int id);

signals:
    void dataReceived(const QByteArray &data);

private:
    explicit HttpClient(QObject *parent = nullptr);

    QNetworkAccessManager *m_networkAccessManager = nullptr;
    static HttpClient *m_instance;
};

#endif // HTTPCLIENT_H