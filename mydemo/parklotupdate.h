#ifndef PARKLOTUPDATE_H
#define PARKLOTUPDATE_H

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include<QFileInfo>
#include<QDir>
#include<QXmlStreamReader>
#include<QXmlStreamWriter>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include "myhelper.h"

class ParklotUpdate: public QObject
{
    Q_OBJECT
public:
    ParklotUpdate();

    //void  CheckNew(const QString&url);
    void  DownloadFile(const QString&url);
    void  UpdateXML();
    bool  ExistPath();
    QString  readXML(bool o);

    bool checkinfo(const QString & localinfo,const QMap<QString, QString> &serverinfomap);
    //
    void CreateDirtory(const QString & path);
    // void  CopycofFile();
    void  Uninstallser();
    void  Installser();
    bool  HasInstallSuccess();
    void  DownUpdateFile();
    //
    void  RecvJson(const QByteArray &byteArray);
    bool  comand(const QStringList &args );
    void  execute() ;

    void  UninstallserServer();
    void  InstallserServer();
    void  StopServer();

public slots:
    void  replyFinished(QNetworkReply* reply);
    void  readyRead();

private :
    QString infoUrl ;
    QString tempUpdatePath;
    int inisialized ;

public:
    QString downloadUrl ;
    //  QFile updaterXmlFiles ;
    bool availableUpdate ;
    QString file_name ;
    QString new_version;
    QString current_version ;
    QMap<QString, QString>  serverinfomap;
    QString localinfo;
    QString  downfilepath;
    // http
    QString m_strFileName;
    QUrl  m_url;

    QNetworkReply *m_pReply;
    QNetworkAccessManager *manager;
    QNetworkRequest   m_req;
    //xml
    QXmlStreamReader m_xml;
    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
};

#endif // PARKLOTUPDATE_H
