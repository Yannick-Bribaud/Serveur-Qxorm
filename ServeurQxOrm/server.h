#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server: public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent=nullptr);

private:
    QTcpServer * serveur;
    QList<QTcpSocket *>listClient;
};

#endif // SERVER_H
