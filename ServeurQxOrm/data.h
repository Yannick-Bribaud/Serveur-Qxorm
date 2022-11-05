#ifndef DATA_H
#define DATA_H
#include <QMetaType>
#include <QString>
#include <QDate>

typedef struct data{

    QString sender;
    QString message;
    QString receiver;
    QString duration;
    QString typemessage;
    QString idRequete;
    QDate dateBegin;
    QDate dateEnd;
    QDate msgDate;
    QTime msgTime;

      friend QDataStream &operator<<(QDataStream & out, const data & data){
          out << data.sender;
          out << data.message;
          out << data.receiver;
          out << data.duration;
          out << data.typemessage;
          out << data.idRequete;
          out << data.dateBegin;
          out << data.dateEnd;
          out << data.msgDate;
          out << data.msgTime;
          return  out;
      }

      friend QDataStream &operator>>(QDataStream & in, data & data){
          in >> data.sender;
          in >> data.message;
          in >> data.receiver;
          in >> data.duration;
          in >> data.typemessage;
          in >> data.idRequete;
          in >> data.dateBegin;
          in >> data.dateEnd;
          in >> data.msgDate;
          in >> data.msgTime;
          return  in;
      }

} Data;

Q_DECLARE_METATYPE(Data);
Data * getNewData();

#endif // DATA_H
