#ifndef BASECLASS_H
#define BASECLASS_H

#include <QObject>

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

  void sethead(const QString &h);
  void setlen(const QString &h);
  void setpack_type(const QString &h);
  void settimestamp(const QString &h);
  void setversion(const QString &h);
  void setdata(const QString &h);
  void setsign_type(const QString &h);
  void setsign(const QString &h);

protected:
    QString  head; //标识字节 长度20
    QString  len;  //长度     长度4
    QString  pack_type;//命令字 长度2
    QString  timestamp;//时间戳  长度19
    QString  version;//协议版本    长度3
    QString  data;//数据域        未固定
    QString  sign_type;//校验码类型  长度10
    QString  sign;//校验码  长度256

};

#endif // BASECLASS_H
