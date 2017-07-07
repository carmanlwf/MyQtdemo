#ifndef BASECLASS_H
#define BASECLASS_H

#include <QObject>

#include<myhelper.h>
#include<myaction.h>



class BaseClass
{

public:
    BaseClass();
    //基础接收类
  QString  gethead();
  QString  getlen();
  QString  getpack_type();
  QString  gettimestamp();
  QString  getversion();
  QString  getdata();
  QString  getsign_type();
  QString  getsign();

  static   BaseClass Convert(const QByteArray &res);
  static   QByteArray Package(const QString &park_id,int len,const QString &action,
                              int result,const QString &recdata,const QString &recsign);

  void sethead(const QString &h);
  void setlen(const QString &h);
  void setpack_type(const QString &h);
  void settimestamp(const QString &h);
  void setversion(const QString &h);
  void setdata(const QString &h);
  void setsign_type(const QString &h);
  void setsign(const QString &h);

  void splitjson(const QString &jsondata);

protected:
    QString  head; //标识字节 长度20
    QString  len;  //长度     长度4
    QString  pack_type;//命令字 长度2
    QString  timestamp;//时间戳  长度19
    QString  version;//协议版本    长度3
    QString  data;//数据域        未固定
    QString  sign_type;//校验码类型  长度10
    QString  sign;//校验码  长度256

     QMap<QString,QString> m_parkidmap;
     QMap<QString,QString> m_commadmap;


};

#endif // BASECLASS_H
