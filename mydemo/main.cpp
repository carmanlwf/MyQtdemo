
#include <QApplication>
// #include "psapi.h"
#include<windows.h>
#include<QDebug>
#include<QProcess>
#include"winnt.h"
#include"winreg.h"
#include"tlhelp32.h"
//判断进程是否存在返回为0就是存在
#include"myhelper.h"
#include"mytcpserver.h"
#include<QTextCodec>
#include"parklotupdate.h"
#include<QSettings>
#include<QDir>
#include<QFileInfo>
#include<QProcess>
#include<QThread>


#include <qmqtt.h>
#include <QCoreApplication>
#include <QTimer>
#include <QtXlsx>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    // xml
    /*
         XMLHelper  m_xml;

         qDebug()<<"UploadLog:"<<m_xml.GetNodeValue("UploadLog");
         qDebug() <<"File: version_code:"<<m_xml.GetAttributesValue("File","version_code");
         qDebug() <<"File: release_date:"<<m_xml.GetAttributesValue("File","release_date");

         m_xml.SetNodeValue("UploadLog","2017-06-14");
         m_xml.SetAttributesValue("File","version_code","2017061406");

        qDebug()<<"UploadLog:"<<m_xml.GetNodeValue("UploadLog");
        qDebug() <<"File: version_code:"<<m_xml.GetAttributesValue("File","version_code");
*/

    //进程测试

    /*
    const char*  DES="cmd.exe";
    DWORD   pid  = GetProcessidFromName(DES);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));


     if (pid)
     {
        //进程已存在
        qDebug()<<"pid:"<<pid;

         if( !KillProcess(pid))
         {
             qDebug()<<"关闭进程失败";
         }

     }
     else
     {
         //重启进程

         QProcess cmd(0);
         QStringList str;
         str << "";
         cmd.startDetached(DES);
         //cmd.waitForFinished();
         qDebug()<<QString::fromLocal8Bit(cmd.readAllStandardError());

     }
     */

    // 网络测试
    /*
    ParklotUpdate p;
        if(!p.availableUpdate)
        {
            p.DownUpdateFile();
        }
        */
    // 注册表

    //RegCreateKey函数
    /*
            HKEY Key;
            QString skey = "Software\Microsoft\Windows\CurrentVersion\App Paths";
            QString strdata = "www.mingrisoft.com";
            RegCreateKey(HKEY_CURRENT_USER, skey.toStdWString().c_str(), &Key);
            if(ERROR_SUCCESS == RegSetValue(Key, NULL, REG_SZ,  strdata.toStdWString().c_str(), strdata.length()))
            {
                qDebug()<<"写入成功!";
             //   MessageBox("写入成功!");
               RegCloseKey(Key);
            }

           //RegQueryValue
            QString skey2 = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\DataManageTools.exe";
            long size;
            wchar_t  *buf=new wchar_t[128];
           // int iret = RegQueryValue(HKEY_LOCAL_MACHINE, skey2.toStdWString().c_str(), buf, &size);
           //    int iret = RegQueryValueEx(HKEY_LOCAL_MACHINE, skey2.toStdWString().c_str(), buf, &size);
            if(0 == iret)
            {
                QString Value;
                //buf[size] = 0;
                Value=QString(Wchar_tToString(buf));

                qDebug()<<"value:"<<Value;
               // MessageBox(Value, "值项是", MB_OK);
            }
            qDebug()<<"iret:"<<iret;
            delete buf;
            buf=NULL;

        //打开注册表项
            HKEY key;
            DWORD dispos;
            SECURITY_ATTRIBUTES sa;
            QString skey = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\DataManageTools.exe";
            sa.nLength = sizeof(SECURITY_ATTRIBUTES);
            sa.bInheritHandle = TRUE;
            sa.lpSecurityDescriptor = NULL;
            DWORD value = 1;
            long iret = RegCreateKeyEx(HKEY_LOCAL_MACHINE, skey.toStdWString().c_str(), NULL, NULL,
                                    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                                    &sa, &key, &dispos);
            if(0 == iret)
            {
                DWORD size;
                wchar_t  *buf=new wchar_t[128];
                DWORD a = REG_SZ;
                QString item="value";
                //返回项值名为bin的项值内容
                int ret = RegQueryValueEx(key, item.toStdWString().c_str(), NULL, &a, (BYTE *)buf, &size);
                if(0 == ret)
                {
                   // buf[size] = 0;
                  //  CString Value;
                   // Value.Format ("%s", buf);
                   // MessageBox(Value, "值项是", MB_OK);

                    QString Value;
                    //buf[size] = 0;
                    Value=QString(Wchar_tToString(buf));

                    qDebug()<<"value:"<<Value;
                   // MessageBox(Value, "值项是", MB_O
                }
                qDebug()<<"ret:"<<ret;
            }
            qDebug()<<"iret"<<iret;
*/

    /*
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\DataManageTools.exe",QSettings::NativeFormat);
    QString value = settings.value("value").toString();//读


    QString path;
    QFileInfo f(value);
    path= f.dir().path();

     //myInstall.bat ;
    //myUninstall.bat

    path +="/msiexec.exe";
  //  path.replace("/","\\");
    qDebug()<<"path"<<path;

    QStringList arguments;
    arguments << "/x "<<"{6F493981-FB85-4282-8BAF-F9373FE83F92}"<<"/qn";
    QProcess p;
    p.start(path,arguments);

    if (p.waitForStarted())
    {
        p.waitForFinished();
        qDebug() <<QString::fromLocal8Bit(p.readAllStandardOutput());
    }
    else
    {
        qDebug() << "Failed to start";

    }

    */
    //system("E:\\PersonalInformation\\my.bat");
   // system("E:\\PersonalInformation\\Uninstall.bat");

    //复制文件
    /*
        QString toDir , sourceDir;

        sourceDir="Update.xml";
        toDir="F:/qt_example_and_Means/aaqmldemo/mydemo/release/Update.xml";
        bool coverFileIfExist=true;

          toDir.replace("\\","/");
          if (sourceDir == toDir){
             // return true;
          }
          if (!QFile::exists(sourceDir)){
              qDebug()<<"file not find";
          }
          QDir *createfile   = new QDir();
          bool exist = createfile->exists(toDir);
          if (exist){
              if(coverFileIfExist){
                  createfile->remove(toDir);
              }
          }//end if

          if(!QFile::copy(sourceDir, toDir))
          {
                 qDebug()<<"copy error";
          }
         */
    //version
   /*
    QDateTime dateTime = QDateTime::currentDateTime();
    QString date = dateTime.toString("yyyy-MM-dd-hh-mm-ss-zzz");
    QString  m_strFileName =MyHelper::GetPath(true)+ QString("/temp/%1.tmp").arg(date);
    qDebug()<<"filename"<<MyHelper::exeVersion(m_strFileName);
    */

    //流程

    //重启进程
    /*
   QFileInfo  aa(MyHelper::GetPath(false));
   qDebug()<<"filename"<<aa.fileName();

   if (!MyHelper::GetProcessidFromName(aa.fileName().toStdString().c_str()))
   {
       QProcess p;
       p.start(MyHelper::GetPath(false));
       if (p.waitForStarted())
       {
           p.waitForFinished();
           qDebug() <<QString::fromLocal8Bit(p.readAllStandardOutput());
          // return true;
       }
       else
       {
           qDebug() << "Failed ";
          // return  false;
       }
   }*/

    /*
    ParklotUpdate  pa;

    if(pa.availableUpdate)
    {

        //终止进程
        QString  appname="DataManageTools.exe";
        if ( !MyHelper::GetProcessidFromName(appname.toStdString().c_str()))
        {
            qDebug()<<"进程不存在";
        }

        if (!MyHelper::KillProcess(MyHelper::GetProcessidFromName(appname.toStdString().c_str())))
        {
            qDebug()<<"关闭进程失败";
        }

       pa.DownUpdateFile();

     while (pa.downfilepath.isEmpty())
      {

       QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
     //   QThread::sleep(500);

      }
      pa.StopServer();

     //QString   oldpath = MyHelper::GetPath(true)+"/config/SystemConfig.xml";
     //QString   newpath = MyHelper::GetPath(true)+"/temp/SystemConfig.xml";
     // MyHelper::copyFileToPath(oldpath ,newpath ,true);
     // pa.copyFileToPath("","",true);

      pa.UninstallserServer();

      pa.Uninstallser();

      pa.Installser();

      pa.HasInstallSuccess();

      pa.UpdateXML();

      pa.InstallserServer();


    }
   */
    //停止服务

    //复制配置

     //删除服务
    // QString apppath=MyHelper::GetPath(true)+"/msiexec.exe";


    // QString path=  "D:/Autocontrol/上传工具/temp/DataManageToolsSetup2017061602.msi";
      // pa.downfilepath;
      //myInstall.bat ;
     //myUninstall.bat
    // path +="/myUninstall.bat";

    // path.replace("/","\\");
    /*
     qDebug()<<"path"<<path;

     QStringList arguments;
     //arguments <<"/i "<<path<<"/qn";
     qDebug()<<"arguments"<<arguments;
     QProcess p;
     p.start("cmd.exe", arguments<<"/c"<<"msiexec /x {6F493981-FB85-4282-8BAF-F9373FE83F92} /qn");

     if (p.waitForStarted())
     {
         p.waitForFinished();
         qDebug() <<QString::fromLocal8Bit(p.readAllStandardOutput());
     }
     else
     {
         qDebug() << "Failed to start";

     }
     */
     //卸载软件

     /*
           QString path=MyHelper::GetPath(true);

      //myInstall.bat ;
     //myUninstall.bat
     path +="/myUninstall.bat";
     path.replace("/","\\");
     qDebug()<<"path"<<path;

     QStringList arguments;
     arguments << "/c "<<path;
     QProcess p;
     p.start("cmd",arguments);

     if (p.waitForStarted())
     {
         p.waitForFinished();
         qDebug() <<QString::fromLocal8Bit(p.readAllStandardOutput());
     }
     else
     {
         qDebug() << "Failed to start";

     }
      */

     // 安装软件

     // 配置

     //修改 xml文件

    //7zip
   //qDebug()<<"compress"<< MyHelper::Compress("Update.xml","Update.7z");

    //rsa
    /*
      char priKey[128] = {0};
      char pubKey[128] = {0};
      char seed[1024]  = {0};

      // 生成 RSA 密钥对
      strcpy(priKey, "pri");  // 生成的私钥文件
      strcpy(pubKey, "pub");  // 生成的公钥文件
      strcpy(seed, "seed");
     RSAHelper::GenerateRSAKey(1024, priKey, pubKey, seed);

     qDebug()<<"priKey"<< priKey<<"pubKey"<<pubKey <<"seed"<<seed;

      // RSA 加解密
      char message[1024] = {0};
      cout<<"Origin Text:\t"<<"Hello World!"<<endl<<endl;
      strcpy(message, "Hello World!");
      QString encryptedText =  RSAHelper::RSAEncryptString(pubKey, seed, message);  // RSA 加密
      qDebug()<<"Encrypted Text:\t"<<encryptedText;
      QString decryptedText =  RSAHelper::RSADecryptString(priKey, encryptedText.toStdString().c_str());  // RSA 解密
     qDebug()<<"Decrypted Text:\t"<<decryptedText;
     */

    //MyTcpServer tcp(8080);

    //mqtt

  //   MqttHelper  mqtt;
    //mqtt.Connect();
           QXlsx::Document xlsx;
            xlsx.write("A1", "Hello Qt!");
            xlsx.saveAs("Test.xlsx");

    return a.exec();
}

