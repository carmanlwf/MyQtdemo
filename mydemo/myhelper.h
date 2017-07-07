#ifndef MYHELPER_H
#define MYHELPER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include<QDomDocument>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QTcpServer>
#include<QFile>
#include<windows.h>

#include<QDebug>
#include<QProcess>
#include<QSettings>
#include<QDir>
#include<QFileInfo>
#include"winnt.h"
#include"winver.h"
#include"tlhelp32.h"
// 加密
#include "randpool.h"
#include "rsa.h"
#include "hex.h"
#include "files.h"
#include <iostream>
#include "LzmaUtil.h"

//qmqtt
#include <qmqtt.h>
#include<qmqtt_client.h>
#include <QCoreApplication>
#include <QTimer>
#include<QHostAddress>
#include<QTextStream>



//#pragma comment(lib, "Version")
//#pragma comment(lib, "cryptlib.lib")
using namespace CryptoPP;
using namespace std;

class RSAHelper
{

  public:
    RSAHelper();

   static QString Encrypt(const QString& content, const QString& privitekey);
   static bool Verify(const QString& content, const QString& privitekey);
   QString  privitekey,DefaultEncoding;

  static void GenerateRSAKey(unsigned int keyLength, const char *privFilename, const char *pubFilename, const char *seed);
  static QString  RSAEncryptString(const char *pubFilename, const char *seed, const char *message);
  static QString  RSADecryptString(const char *privFilename, const char *ciphertext);
  static RandomPool & GlobalRNG();


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

class MqttHelper: public QObject
{
    Q_OBJECT

public:
    MqttHelper(QObject *parent = 0);
    QTimer _timer;
    quint16 _number;

public slots:
     void   Connect();
     void   Subscribe();
     void   publish();
     void     MqttMsgSubscribed();
     QString   MqttMsgPublishReceived();
     void      ConnectionClosed();

     void  onTimeout();
     void  onDisconnected();
  // QString   Mqttclient;

     void  onSubscribed(const QString& topic);

     void  onReceived(const QMQTT::Message& message);

private:
    QMQTT::Client * _client;
    QMQTT::Client *  _Subscriber;

};

class XMLHelper
{
public:
    XMLHelper() {}
 static QString  ReadXML(const QString&filepath);
 static void WriteXML(const QString& content, const QString& savepath);


 //xml

 //
  QString  GetNodeValue(const QString&nodename);

  QString  GetAttributesValue(const QString&nodename, const QString&Attributesname);

   void  SetNodeValue(const QString&nodename,const QString&nodevalue);
   void  SetAttributesValue(const QString&nodename,const QString&Attributesname,const QString&Attributevalue);

  QString  errorString() const;  // 错误信息
  void  loadfile();

  QXmlStreamReader xml;
  QXmlStreamWriter m_writer;
  QDomDocument doc;
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



  // 字节转KB、MB、GB
  static QString size(qint64 bytes);

  // 速度转KB/S、MB/S、GB/S
 static QString speed(double speed);

  // 秒转*d *h *m *s
 static QString timeFormat(int seconds);

 //宽字符转换
  static char* Wchar_tToString( wchar_t *wchar);

  // 通过进程名称获取pid
  static DWORD GetProcessidFromName(const char *name);
   //通过pid终止进程
  static BOOL KillProcess(DWORD ProcessId);

  static  bool  ExistPath();
  static QString GetPath(bool is_folder);
  static bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
  static bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
  static QString exeVersion(const QString &exePath);


  // SZ_OK               - 0	OK
  //  SZ_ERROR_MEM        - 2	Memory allocation error
  //  SZ_ERROR_DATA		- 1	Data error
  static   int Compress(char* pSrcFile, char* pDstFile);
  static   int Uncompress(char* pSrcFile, char* pDstFile);

};

#endif // MYHELPER_H
