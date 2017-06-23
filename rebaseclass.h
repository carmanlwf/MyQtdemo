#ifndef REBASECLASS_H
#define REBASECLASS_H

#include <QObject>

class ReBaseClass
{
public:
    ReBaseClass();

    // 基础回复类
    QString  gethead();
    QString  getlen();
    QString  getpack_type();
    QString  getdata();
    QString  getresult();
    QString  getsign();

    void sethead(const QString &h);
    void setlen(const QString &h);
    void setpack_type(const QString &h);

    void setdata(const QString &h);
    void setresult(const QString &h);
    void setsign(const QString &h);
protected:

    QString  park_id; //标识字节 长度20
    QString  len;  //长度     长度4
    QString  pack_type;//命令字 长度2
    QString  result;//结果  长度1
    QString  data;//数据域        未固定
    //QString  sign_type;//校验码类型  长度10
    QString  sign;//校验码  长度256
};

#endif // REBASECLASS_H
