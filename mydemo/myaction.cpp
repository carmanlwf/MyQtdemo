#include "myaction.h"

MyAction::MyAction()
{

}


void ActionHeart_beat::recvjson(const QString &jsondata){
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsondata.toLocal8Bit(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("action")) {
                QJsonValue value = object.value("action");
                if (value.isString()) {
                    action= value.toString();
                }
            }
            if (object.contains("park_id")) {
                QJsonValue value = object.value("park_id");
                if (value.isString()) {
                    park_id = value.toString();

                }
            }
        }
    }
    else{
        qDebug()<<"json error"<<jsonError.errorString();
    }
}



void ActionRegiser::recvjson(const QString &jsondata)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsondata.toLocal8Bit(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("action")) {
                QJsonValue value = object.value("action");
                if (value.isString()) {
                    action= value.toString();
                }
            }
            if (object.contains("park_id")) {
                QJsonValue value = object.value("park_id");
                if (value.isString()) {
                    park_id = value.toString();

                }
            }
            if (object.contains("park_name")) {
                QJsonValue value = object.value("park_name");
                if (value.isString()) {
                    park_name= value.toString();
                }
            }
            if (object.contains("time")) {
                QJsonValue value = object.value("time");
                if (value.isString()) {
                    time = value.toString();

                }
            }
            if (object.contains("address")) {
                QJsonValue value = object.value("address");
                if (value.isString()) {
                    address = value.toString();

                }
            }
            if (object.contains("phone")) {
                QJsonValue value = object.value("phone");
                if (value.isString()) {
                    phone= value.toString();
                }
            }
            if (object.contains("contacts")) {
                QJsonValue value = object.value("contacts");
                if (value.isString()) {
                    contacts = value.toString();

                }
            }
        }
    }
    else{
        qDebug()<<"json error"<<jsonError.errorString();
    }
}

void ActionOut::recvjson(const QString &jsondata){
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsondata.toLocal8Bit(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("action")) {
                QJsonValue value = object.value("action");
                if (value.isString()) {
                    action= value.toString();
                }
            }
            if (object.contains("park_id")) {
                QJsonValue value = object.value("park_id");
                if (value.isString()) {
                    park_id = value.toString();

                }
            }
            if (object.contains("car_no")) {
                QJsonValue value = object.value("car_no");
                if (value.isString()) {
                    car_no= value.toString();
                }
            }
            if (object.contains("record_id")) {
                QJsonValue value = object.value("record_id");
                if (value.isString()) {
                    record_id = value.toString();

                }
            }
            if (object.contains("out_time")) {
                QJsonValue value = object.value("out_time");
                if (value.isString()) {
                    out_time = value.toString();
                }
            }
            if (object.contains("charge_mechod")) {
                QJsonValue value = object.value("charge_mechod");
                if (value.isString()) {
                    charge_mechod= value.toString();
                }
            }
            if (object.contains("export_name")) {
                QJsonValue value = object.value("export_name");
                if (value.isString()) {
                    export_name = value.toString();

                }
            }
            if (object.contains("card_type")) {
                QJsonValue value = object.value("card_type");
                if (value.isDouble()) {
                    card_type = value.toInt();

                }
            }
        }
    }
    else{
        qDebug()<<"json error"<<jsonError.errorString();
    }
}

void ActionIn::recvjson(const QString &jsondata)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsondata.toLocal8Bit(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("action")) {
                QJsonValue value = object.value("action");
                if (value.isString()) {
                    action= value.toString();
                }
            }
            if (object.contains("park_id")) {
                QJsonValue value = object.value("park_id");
                if (value.isString()) {
                    park_id = value.toString();

                }
            }
            if (object.contains("car_no")) {
                QJsonValue value = object.value("car_no");
                if (value.isString()) {
                    car_no= value.toString();
                }
            }
            if (object.contains("record_id")) {
                QJsonValue value = object.value("record_id");
                if (value.isString()) {
                    record_id = value.toString();

                }
            }
            if (object.contains("in_time")) {
                QJsonValue value = object.value("in_time");
                if (value.isString()) {
                    in_time = value.toString();

                }
            }
            if (object.contains("charge_mechod")) {
                QJsonValue value = object.value("charge_mechod");
                if (value.isString()) {
                    charge_mechod= value.toString();
                }
            }
            if (object.contains("entry_name")) {
                QJsonValue value = object.value("entry_name");
                if (value.isString()) {
                    entry_name = value.toString();

                }
            }
            if (object.contains("card_type")) {
                QJsonValue value = object.value("card_type");
                if (value.isDouble()) {
                    card_type = value.toInt();

                }
            }
        }
    }
    else{
        qDebug()<<"json error"<<jsonError.errorString();
    }
}

void ActionPrepay::recvjson(const QString &jsondata){
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsondata.toLocal8Bit(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("action")) {
                QJsonValue value = object.value("action");
                if (value.isString()) {
                    action= value.toString();
                }
            }
            if (object.contains("park_id")) {
                QJsonValue value = object.value("park_id");
                if (value.isString()) {
                    park_id = value.toString();

                }
            }
            if (object.contains("car_no")) {
                QJsonValue value = object.value("car_no");
                if (value.isString()) {
                    car_no= value.toString();
                }
            }

            if (object.contains("pay_mechod")) {
                QJsonValue value = object.value("pay_mechod");
                if (value.isDouble()) {
                    pay_mechod= value.toInt();
                }
            }
            if (object.contains("pay_time")) {
                QJsonValue value = object.value("pay_time");
                if (value.isString()) {
                    pay_time = value.toString();

                }
            }
            if (object.contains("pay_place")) {
                QJsonValue value = object.value("pay_place");
                if (value.isString()) {
                    pay_place = value.toString();

                }
            }
            if (object.contains("pay_money")) {
                QJsonValue value = object.value("pay_money");
                if (value.isDouble()) {
                    pay_money = value.toInt();

                }
            }
            if (object.contains("card_type")) {
                QJsonValue value = object.value("card_type");
                if (value.isDouble()) {
                    card_type = value.toInt();

                }
            }
        }
    }
    else{
        qDebug()<<"json error"<<jsonError.errorString();
    }
}

void ActionPay::recvjson(const QString &jsondata)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsondata.toLocal8Bit(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("action")) {
                QJsonValue value = object.value("action");
                if (value.isString()) {
                    action= value.toString();
                }
            }
            if (object.contains("park_id")) {
                QJsonValue value = object.value("park_id");
                if (value.isString()) {
                    park_id = value.toString();

                }
            }
            if (object.contains("car_no")) {
                QJsonValue value = object.value("car_no");
                if (value.isString()) {
                    car_no= value.toString();
                }
            }
            if (object.contains("record_id")) {
                QJsonValue value = object.value("record_id");
                if (value.isString()) {
                    record_id = value.toString();

                }
            }
            if (object.contains("in_time")) {
                QJsonValue value = object.value("in_time");
                if (value.isString()) {
                    in_time = value.toString();

                }
            }
            if (object.contains("pay_mechod")) {
                QJsonValue value = object.value("pay_mechod");
                if (value.isDouble()) {
                    pay_mechod= value.toInt();
                }
            }
            if (object.contains("pay_time")) {
                QJsonValue value = object.value("pay_time");
                if (value.isString()) {
                    pay_time = value.toString();

                }
            }
            if (object.contains("pay_place")) {
                QJsonValue value = object.value("pay_place");
                if (value.isString()) {
                    pay_place = value.toString();

                }
            }
            if (object.contains("pay_money")) {
                QJsonValue value = object.value("pay_money");
                if (value.isDouble()) {
                    pay_money = value.toInt();

                }
            }
            if (object.contains("stay_time")) {
                QJsonValue value = object.value("stay_time");
                if (value.isDouble()) {
                    stay_time = value.toInt();

                }
            }
            if (object.contains("card_type")) {
                QJsonValue value = object.value("card_type");
                if (value.isDouble()) {
                    card_type = value.toInt();

                }
            }
        }
    }
    else{
        qDebug()<<"json error"<<jsonError.errorString();
    }
}

void ActionRecharge::recvjson(const QString &jsondata)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsondata.toLocal8Bit(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("action")) {
                QJsonValue value = object.value("action");
                if (value.isString()) {
                    action= value.toString();
                }
            }
            if (object.contains("park_id")) {
                QJsonValue value = object.value("park_id");
                if (value.isString()) {
                    park_id = value.toString();

                }
            }
            if (object.contains("car_no")) {
                QJsonValue value = object.value("car_no");
                if (value.isString()) {
                    car_no= value.toString();
                }
            }

            if (object.contains("begin_time")) {
                QJsonValue value = object.value("begin_time");
                if (value.isString()) {
                    begin_time = value.toString();

                }
            }
            if (object.contains("validity_time")) {
                QJsonValue value = object.value("validity_time");
                if (value.isDouble()) {
                    validity_time= value.toInt();
                }
            }

            if (object.contains("charge_fee")) {
                QJsonValue value = object.value("charge_fee");
                if (value.isDouble()) {
                    charge_fee = value.toInt();

                }
            }
            if (object.contains("card_type")) {
                QJsonValue value = object.value("card_type");
                if (value.isDouble()) {
                    card_type = value.toInt();

                }
            }
        }
    }
    else{
        qDebug()<<"json error"<<jsonError.errorString();
    }
}
