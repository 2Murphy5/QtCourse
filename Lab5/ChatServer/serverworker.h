#ifndef SERVERWORKER_H
#define SERVERWORKER_H
#include<QTcpSocket>
#include <QObject>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName()
    {
        return m_userName;
    }
    void setUserName(QString user);
signals:
    void logMessage(const QString &msg);
    void jsonReceived(ServerWorker*sender,const QJsonObject &docObj);
    void disconnectedFromClient();
private:
    QTcpSocket * m_serverSocket;
    QString m_userName;

public slots:
    void onReadyRead();
    void sendMessage(const QString &text,const QString &type="message");
    void sendJson(const QJsonObject &json);
};

#endif // SERVERWORKER_H
