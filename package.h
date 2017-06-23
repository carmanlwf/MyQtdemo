#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>

class Package
{
public:
    Package();

    void  Pack(const QString&data);
    QString  Unpack();

  QString  Receivemsg,Sendmsg;

};

#endif // PACKAGE_H
