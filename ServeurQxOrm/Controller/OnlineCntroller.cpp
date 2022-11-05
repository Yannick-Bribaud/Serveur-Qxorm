#include "OnlineCntroller.h"
#include "ServerUi.h"
#include <QListWidgetItem>

ServerUi * serverUi;
OnlineCntroller::OnlineCntroller(QObject *parent){
    listeClients.clear();
    connect(this,SIGNAL(getListOfClients()),parent,SLOT(setListeOfClient()));
    connect(this,SIGNAL(OnlineUiClosed()),parent,SLOT(OnlineIsClosed()));
}

void OnlineCntroller::setListClient(QList<QTcpSocket *> liste){
    listeClients=liste;
}

void OnlineCntroller::run(){
    onlineUi = new UserOnline(this);
    onlineUi->show();
}



void OnlineCntroller::actualise(){
    emit getListOfClients();
    onlineUi->getListWidget()->clear();

    for(int i=0; i<listeClients.size(); i++){

        client = listeClients[i];
        property_client=client->property("Properties");
        client_Props=property_client.value<Properties>();

        Item=new QListWidgetItem();
        Item->setText(client_Props.clientName);
        Item->setIcon(QIcon(":/icon/Online_1.png"));
        onlineUi->getListWidget()->addItem(Item);
    }

}

void OnlineCntroller::minimized(){
    onlineUi->showMinimized();
}

void OnlineCntroller::closeOnlineUi(){
    onlineUi->close();
    emit OnlineUiClosed();
}

