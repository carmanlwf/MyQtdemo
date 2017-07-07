#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include<QTcpServer>
#include<QTcpSocket>
#include<QDebug>
#include<QDateTime>
#include<QRegExp>

class MyTcpServer: public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer(quint16 port, QObject* parent = 0);

    void incomingConnection(int socket);
    void pause();
    void resume();

private slots:
    void readClient();
    void discardClient();

private:
    bool disabled;
    // const QString appplicationname= "DataManageTools";


};

#endif // MYTCPSERVER_H
