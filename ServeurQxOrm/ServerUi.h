#ifndef SERVERUI_H
#define SERVERUI_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QPoint>
#include <QtNetwork>
#include "server.h"
#include "property.h"
#include "data.h"
#include "Controller/OnlineCntroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ServerUi; }
QT_END_NAMESPACE


class Server;

class ServerUi : public QWidget
{
    Q_OBJECT

public:
    ServerUi(QWidget *parent = nullptr);
    void sendMessage(QVariant & value);
    void sendlistMsgMissed(QVariantList & value);
    void setClientProperties( QVariant & properties, QTcpSocket * sender);
    void setMsgNoSent(QVariant &dataToSend);
    void sendMessageNoSent(QVariant & ReceiverProperty);
    QList<QTcpSocket *>getListOfClient() { return listeClients; }
    QPushButton * getOnlineButton();
    quint16 getPort();

    ~ServerUi();


private slots:
    void nouvelleConnexion();
    void deconnexion();
    void donneesRecues();
    void Online_Clicked();
    void OnRunningClicked();
    void onStopClicked();
    void setListeOfClient();
    void minimizeUi();
    void OnlineIsClosed();

protected:
    QPoint mousePoint;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::ServerUi * ui;
    Server * m_serveur;
    OnlineCntroller * onlineUi;
    quint16 tailleMsg;
    QVariant container;
    Properties properties;
    QList<QTcpSocket *> listeClients;
    QVariantList listeMsgNonEnvoye;
    QVariantList listeMsgByUser;
    Data data;
    bool mouseOff;
    bool isOnlineShow;
};
#endif // SERVERUI_H
