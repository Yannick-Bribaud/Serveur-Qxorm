#include "ServerUi.h"
#include "ui_serverui.h"
#include <QMessageBox>
#include <QDataStream>

QList<int>listeItemToDelete;
ServerUi::ServerUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerUi)
{
        ui->setupUi(this);

        this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        this->setAttribute(Qt::WA_TranslucentBackground);
        m_serveur=new Server(this); isOnlineShow=false;
        this->tailleMsg=0; mouseOff=false; onlineUi=nullptr;

    ui->Running_Button->setIcon(QIcon(":/icon/play_96px.png"));
    ui->StopConnexion_Button->setIcon(QIcon(":/icon/stop_96px.png"));
    ui->StopServer_Button->setIcon(QIcon(":/icon/shutdown_96px.png"));
    ui->Close_Button->setIcon(QIcon(":/icon/close_window48_48px.png"));
    ui->minimizeUi_Button->setIcon(QIcon(":/icon/minimize_window_48px.png"));

    qRegisterMetaTypeStreamOperators<Properties>("Properties");
    qRegisterMetaTypeStreamOperators<Data>("Data");

    connect(ui->Close_Button, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->Running_Button, SIGNAL(clicked()), this, SLOT(OnRunningClicked()));
    connect(ui->StopConnexion_Button, SIGNAL(clicked()), this, SLOT(onStopClicked()));
    connect(ui->StopServer_Button, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(m_serveur,SIGNAL(newConnection()), SLOT(nouvelleConnexion()));
    connect(ui->Online_Button,SIGNAL(clicked()),this,SLOT(Online_Clicked()));
    connect(ui->minimizeUi_Button,SIGNAL(clicked()),this,SLOT(minimizeUi()));

}

quint16 ServerUi::getPort(){
    return ui->Port->value();
}

void ServerUi::sendMessage(QVariant &value){
    //dynamique sending

    QVariant property; Properties props;
    data=value.value<Data>();QString typeMsg;
    typeMsg="newMessage";

    QByteArray paquet;  QTcpSocket * client;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    for(int i=0; i<listeClients.size(); i++){
           client=listeClients[i];

        property=client->property("Properties");
        props=property.value<Properties>();

        if(data.receiver==props.clientName){
            out << quint16(0);
            out << typeMsg;
            out << value;
            out.device()->seek(0);
            out << (quint16)(paquet.size() - sizeof (quint16));
            client->write(paquet);
             break;
        }else{
           container=QVariant::fromValue<Data>(data);
           setMsgNoSent(container);
        }
    }
}

void ServerUi::sendlistMsgMissed(QVariantList &value){

    QVariant property; Properties props;
    QVariant variant; QString typeMsg;
    typeMsg="missedMessages";
    variant=value.at(0);

    data=variant.value<Data>();
    QByteArray paquet;  QTcpSocket * client;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    for(int i=0; i<listeClients.size(); i++){
           client=listeClients[i];

        property=client->property("Properties");
        props=property.value<Properties>();

        if(data.receiver==props.clientName){
            out << quint16(0);
            out <<typeMsg;
            out << value;
            out.device()->seek(0);
            out << (quint16)(paquet.size() - sizeof (quint16));
            client->write(paquet);
             break;
        }else{
           container=QVariant::fromValue<Data>(data);
           setMsgNoSent(container);
        }
    }
}

void ServerUi::setClientProperties(QVariant &properties, QTcpSocket * sender){
    const char * name="Properties";

    for(int i=0; i<listeClients.size(); i++){
      if(listeClients[i]->socketDescriptor()==sender->socketDescriptor()){
            listeClients[i]->setProperty(name,properties);
      }
    }
    sendMessageNoSent(properties);
}


void ServerUi::setMsgNoSent(QVariant &dataToSend){
    listeMsgNonEnvoye.append(dataToSend);
}

void ServerUi::sendMessageNoSent(QVariant &ReceiverProperty){

      Data localdata;QVariant variant;
      listeMsgByUser.clear(); listeItemToDelete.clear();

    if(listeMsgNonEnvoye.isEmpty())
        return;

    properties=ReceiverProperty.value<Properties>();

    for(int i=0; i<listeMsgNonEnvoye.count(); i++){
        variant=listeMsgNonEnvoye.at(i);
        localdata=variant.value<Data>();
          if(localdata.receiver==properties.clientName){        
            listeMsgByUser.append(variant);
            listeItemToDelete.append(i);
        }
    }
        if(listeMsgByUser.isEmpty())
            return;

        sendlistMsgMissed(listeMsgByUser);

     if(listeItemToDelete.count()==listeMsgNonEnvoye.count()){
            listeMsgNonEnvoye.clear();
      }else{
          for(int i=0; i<listeItemToDelete.count();i++){
             listeMsgNonEnvoye.removeAt(listeItemToDelete.at(i));
         }
     }
}

QPushButton *ServerUi::getOnlineButton(){
    return ui->Online_Button;
}

ServerUi::~ServerUi(){
    delete ui;
}

void ServerUi::nouvelleConnexion(){
  QTcpSocket * newClient = m_serveur->nextPendingConnection();
  properties = newClient->property("Properties").value<Properties>();
  listeClients << newClient;

  connect(newClient, SIGNAL(readyRead()),this, SLOT(donneesRecues()));
  connect(newClient, SIGNAL(disconnected()), SLOT(deconnexion()));
}

void ServerUi::deconnexion(){
    QTcpSocket * socket = qobject_cast<QTcpSocket *>(sender());
     if(socket==0)
         return;

    listeClients.removeOne(socket);
    socket->deleteLater();
}

void ServerUi::donneesRecues(){

    quint8 checkTypeData;
    QTcpSocket * socket = qobject_cast<QTcpSocket *>(sender());

    if(socket==0){
        return;
    }
    QDataStream in(socket);

    if(tailleMsg==0){
        if(socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> tailleMsg;
    }

    if(socket->bytesAvailable() < tailleMsg) return;
    in >> checkTypeData;

    if(checkTypeData=='P'){
        in >> container;
        setClientProperties(container,socket);
    }
    else{
      in >> container;
      sendMessage(container);
    }
    tailleMsg=0;
}

void ServerUi::mousePressEvent(QMouseEvent *event){
   if(event->button()==Qt::LeftButton) {
       mouseOff=true;
    }
}

void ServerUi::mouseReleaseEvent(QMouseEvent *event){
    if(event->Close){
        mouseOff=false;
    }
}

void ServerUi::mouseMoveEvent(QMouseEvent *event){
    mousePoint=event->globalPos();
    move(mousePoint);
}

void ServerUi::Online_Clicked(){
    if(!isOnlineShow){
      onlineUi = new OnlineCntroller(this);
      onlineUi->run();
      isOnlineShow=true;
   }
}

void ServerUi::OnRunningClicked()
{
    if(!m_serveur->listen(QHostAddress::LocalHost,getPort())){
        QMessageBox::critical(this,"Error",m_serveur->errorString());
    }
    else{
        QMessageBox::information(this,"Serveur","Server is Running");
       ui->Running_Button->setEnabled(false);
    }
}

void ServerUi::onStopClicked(){
   if(m_serveur->isListening()){
        m_serveur->close();
        ui->Running_Button->setEnabled(true);
        QMessageBox::information(this,"Serveur","Server Stopped listenning");
   }
}
void ServerUi::setListeOfClient(){
    onlineUi->setListClient(listeClients);
}

void ServerUi::minimizeUi(){
    this->showMinimized();
}

void ServerUi::OnlineIsClosed(){
    isOnlineShow=false;
    delete onlineUi;
}






