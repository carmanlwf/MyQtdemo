#ifndef MYHELPER_H
#define MYHELPER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QTcpServer>

class RSAHelper
{

  public:
    RSAHelper();

   static QString Encrypt(const QString& content, const QString& privitekey);
   static bool Verify(const QString& content, const QString& privitekey);

   QString  privitekey,DefaultEncoding;

};

class SocketHelper
{


public:
  SocketHelper();


  static void  Connect();

  static void  Send(const QString&data);

  static void Listening();

  static QString Received();

  QTcpServer  SocketServer;


};



class HttpHelper
{
public:
    HttpHelper() {}

  //  static void UploadFile(const QString& url, NameValueCollection data, Encoding encoding);
  //  static void UploadFile(const QString& url, string[] files, NameValueCollection data, Encoding encoding);

  QString  DefaultEncoding;
};

class MqttHelper
{
public:
    MqttHelper() {}
    static void Connect();
    static void  Subscribe();
    static void   MqttMsgSubscribed();
    static QString   MqttMsgPublishReceived();
    static void  ConnectionClosed();

   QString   Mqttclient;
};

class XMLHelper
{
public:
    XMLHelper() {}
 static QString  ReadXML(const QString&filepath);
 static void WriteXML(const QString& content, const QString& savepath);
 QString FilePath;

};

class LogInfo
{
public:
    LogInfo() {}

   static void SaveLog();
   QString LogPath,LogString,LogLevel;

};

class MyHelper
{

public:
    MyHelper();
  static QString  GetApplicationPath();
  static QString  GetIPAddress();

};

#endif // MYHELPER_H
