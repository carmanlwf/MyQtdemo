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
