#include "baseclass.h"

BaseClass::BaseClass()
{

}

QString BaseClass::gethead()
{
    return head;
}

QString BaseClass::getlen()
{
    return len;
}

QString BaseClass::getpack_type()
{
    return pack_type;
}

QString BaseClass::gettimestamp()
{
    return timestamp;
}

QString BaseClass::getversion()
{
    return version;
}

QString BaseClass::getdata()
{
    return data;
}

QString BaseClass::getsign_type()
{
    return sign_type;
}

QString BaseClass::getsign()
{
    return sign;
}

BaseClass BaseClass::Convert(const QByteArray &res)
{
    BaseClass  entity ;
    entity.head=res.left(20);
    entity.len=res.mid(21,4);
    int datalen=res.size();

    // 判断长度
    if(datalen==entity.len.toInt() )
    {
     entity.pack_type=res.mid(25,2);
     entity.timestamp=res.mid(27,19);
     entity.version=res.mid(46,3);

     entity.data=res.mid(49,datalen-49-266);
     entity.sign_type=res.mid(datalen-266,10);
     entity.sign=res.right(256);

     // 判断加密
       if (entity.sign==RSAHelper::RSAEncryptString("pubkey","seed",entity.data.toStdString().c_str()))
       {
/*
           switch (entity.pack_type)
           {

           case "Register":
               ActionRegiser a;
               a.recvjson(entity.data);
               break;
           case "Heart_beat":
               ActionRegiser a;
               a.recvjson(entity.data);
               break;
           case "In":
               ActionRegiser a;
               a.recvjson(entity.data);
               break;
           case "Out":
               ActionRegiser a;
               a.recvjson(entity.data);
               break;
           case "Pay":
               ActionRegiser a;
               a.recvjson(entity.data);
               break;
           case "Recharge":
               ActionRegiser a;
               a.recvjson(entity.data);
               break;
           case "OnlinePay":
               ActionRegiser a;
               a.recvjson(entity.data);
               break;
           default:
               break;
           }
*/

           return  entity;
       }
        else
       {

           qDebug()<<"加密比对错误";
       }

    }
    else
    {
        qDebug()<<"数据包长度不正确";
    }
    return  entity;

}

QByteArray BaseClass::Package(const QString &park_id, int len, const QString &action, int result, const QString &recdata, const QString &recsign)
{
     QString d=QString("%1%2%3%4%5%6").arg(park_id).arg(len).arg(action).arg(result).arg(recdata).arg(recsign);

     return  d.toLocal8Bit();

}

void BaseClass::sethead(const QString &h)
{
    head=h;
}

void BaseClass::setlen(const QString &h)
{
    len=h;
}

void BaseClass::setpack_type(const QString &h)
{
    pack_type=h;
}

void BaseClass::settimestamp(const QString &h)
{
    timestamp=h;
}

void BaseClass::setversion(const QString &h)
{
    version=h;
}

void BaseClass::setdata(const QString &h)
{
    data=h;
}

void BaseClass::setsign_type(const QString &h)
{
    sign_type=h;
}

void BaseClass::setsign(const QString &h)
{
    sign=h;
}

void BaseClass::splitjson(const QString &jsondata)
{

  QString a =  jsondata;


}
