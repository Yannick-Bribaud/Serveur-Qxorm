#include "property.h"

Properties * getNewDataStruct(){
     Properties * property = new Properties();
     return property;
}


Properties * setDataInStruct(Properties * property, const QString &SenderName, const QString &idSender){
    property->clientName = SenderName;
    property->matricule = idSender;
    return property;
}

Properties *SendInfo(Properties *property, const QString &SenderName, const QString &idSender){
    property->clientName = SenderName;
    property->matricule = idSender;

    return property;
}
