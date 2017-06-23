#include "rebaseclass.h"

ReBaseClass::ReBaseClass()
{

}
QString ReBaseClass::gethead()
{
    return park_id;
}

QString ReBaseClass::getlen()
{
    return len;
}

QString ReBaseClass::getpack_type()
{
    return pack_type;
}





QString ReBaseClass::getdata()
{
    return data;
}

QString ReBaseClass::getresult()
{
    return  result;
}



QString ReBaseClass::getsign()
{
    return sign;
}

void ReBaseClass::sethead(const QString &h)
{
    park_id=h;
}

void ReBaseClass::setlen(const QString &h)
{
    len=h;
}

void ReBaseClass::setpack_type(const QString &h)
{
    pack_type=h;
}



void ReBaseClass::setdata(const QString &h)
{
    data=h;
}

void ReBaseClass::setresult(const QString &h)
{
    result=h;
}



void ReBaseClass::setsign(const QString &h)
{
    sign=h;
}
