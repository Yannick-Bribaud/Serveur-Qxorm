#ifndef PROPERTY_H
#define PROPERTY_H
#include <QString>
#include <QMetaType>
#include <QDate>

typedef struct properties
{
    QDate dateConnexion;
    QString clientName;
    QString matricule;
    QDate dateDeconnexion;

    friend QDataStream &operator<<(QDataStream & out, const properties & properties){
        out << properties.dateConnexion;
        out << properties.clientName;
        out << properties.matricule;
        out << properties.dateDeconnexion;
        return  out;
    }

    friend QDataStream &operator>>(QDataStream & in, properties & properties){
        in >> properties.dateConnexion;
        in >> properties.clientName;
        in >> properties.matricule;
        in >> properties.dateDeconnexion;
        return in;
    }


}Properties;

Q_DECLARE_METATYPE (Properties)

Properties * getNewDataStruct();
Properties * setDataInStruct(Properties * dataOfSocket,const QString & SenderName, const quint8 & idSender);
Properties * SendInfo(Properties * dataOfSocket,const QString & SenderName, const quint8 & idSender);



#endif // PROPERTY_H
