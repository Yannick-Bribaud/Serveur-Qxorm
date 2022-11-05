#ifndef ONLINECNTROLLER_H
#define ONLINECNTROLLER_H

#include <QObject>
#include "UserOnline.h"
#include <QTcpSocket>
#include "property.h"
#include "data.h"

class OnlineCntroller :public QObject
{
    Q_OBJECT

public:
    OnlineCntroller(QObject * parent);
    void setListClient(QList<QTcpSocket *>liste);
    QString getTextItem() const { return textItem; }
    void run();

signals:
    void getListOfClients();
    void OnlineUiClosed();
    void disconnectClientOnServer();

private slots:
    void actualise();
    void minimized();
    void closeOnlineUi();

private:
    UserOnline * onlineUi;
    QList<QTcpSocket *> listeClients;
    QTcpSocket * client;
    Properties client_Props;
    QVariant property_client;
    QListWidgetItem * Item;
    QString textItem;
};

#endif // ONLINECNTROLLER_H
