#ifndef MYACTION_H
#define MYACTION_H

#include <QObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include<QDebug>

class ActionRegiser
{
    QString  action;
    QString  park_id;
    QString  park_name;
    QString  time;
    QString  address;
    QString  phone;
    QString  contacts;
public:
    void  recvjson(const QString &jsondata);
};

class ActionIn
{
    QString  action;
    QString  park_id;
    QString  car_no;
    QString  record_id;
    QString  in_time;

    int  card_type;
    QString  charge_mechod;
    QString  entry_name;
public:

    void  recvjson(const QString &jsondata);
};
class ActionRecharge
{
    QString  action;
    QString  park_id;
    QString  car_no;
    int  card_type;
    unsigned int charge_fee;
   // QString  charge_mechod;
   // QString  entry_name;
    QString  begin_time;
    QString  validity_time;
public:

    void  recvjson(const QString &jsondata);
};
class ActionOut
{
    QString  action;
    QString  park_id;
    QString  car_no;
    QString  record_id;
    QString  out_time;

    int  card_type;
    QString  charge_mechod;
    QString  export_name;
public:

    void  recvjson(const QString &jsondata);
};
class ActionHeart_beat
{
    QString  action;
    QString  park_id;
public:

    void  recvjson(const QString &jsondata);
};
class ActionPay
{

    QString  action;
    QString  park_id;
    QString  car_no;
    QString  record_id;
    int  card_type;
    QString in_time;
    unsigned int pay_money;
    unsigned int stay_time;
    QString  pay_time;
    int  pay_mechod;
    QString  pay_place;
public:

    void  recvjson(const QString &jsondata);
};
class ActionPrepay
{
    QString  action;
    QString  park_id;
    QString  car_no;
    int  card_type;
    unsigned int pay_money;
    QString  pay_time;
    int  pay_mechod;
    QString  pay_place;

public:

    void  recvjson(const QString &jsondata);

};



class MyAction
{
public:
    MyAction();

    void  ActionRegiser();
    void  ActionIn();
    void  ActionOut();
    void  ActionHeart_beat();
    void  ActionPay();
    void  ActionOnlinePay();
};

#endif // MYACTION_H
