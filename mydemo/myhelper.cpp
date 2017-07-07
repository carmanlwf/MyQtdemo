#include "myhelper.h"

MyHelper::MyHelper()
{

}

QString MyHelper::size(qint64 bytes)
{
    QString strUnit;
    double dSize = bytes * 1.0;
    if (dSize <= 0)
    {
        dSize = 0.0;
    }
    else if (dSize < 1024)
    {
        strUnit = "Bytes";
    }
    else if (dSize < 1024 * 1024)
    {
        dSize /= 1024;
        strUnit = "KB";
    }
    else if (dSize < 1024 * 1024 * 1024)
    {
        dSize /= (1024 * 1024);
        strUnit = "MB";
    }
    else
    {
        dSize /= (1024 * 1024 * 1024);
        strUnit = "GB";
    }

    return QString("%1 %2").arg(QString::number(dSize, 'f', 2)).arg(strUnit);
}

QString MyHelper::speed(double speed)
{
    QString strUnit;
    if (speed <= 0)
    {
        speed = 0;
        strUnit = "Bytes/S";
    }
    else if (speed < 1024)
    {
        strUnit = "Bytes/S";
    }
    else if (speed < 1024 * 1024)
    {
        speed /= 1024;
        strUnit = "KB/S";
    }
    else if (speed < 1024 * 1024 * 1024)
    {
        speed /= (1024 * 1024);
        strUnit = "MB/S";
    }
    else
    {
        speed /= (1024 * 1024 * 1024);
        strUnit = "GB/S";
    }

    QString strSpeed = QString::number(speed, 'f', 2);
    return QString("%1 %2").arg(strSpeed).arg(strUnit);
}

QString MyHelper::timeFormat(int seconds)
{
    QString strValue;
    QString strSpacing(" ");
    if (seconds <= 0)
    {
        strValue = QString("%1s").arg(0);
    }
    else if (seconds < 60)
    {
        strValue = QString("%1s").arg(seconds);
    }
    else if (seconds < 60 * 60)
    {
        int nMinute = seconds / 60;
        int nSecond = seconds - nMinute * 60;

        strValue = QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }
    else if (seconds < 60 * 60 * 24)
    {
        int nHour = seconds / (60 * 60);
        int nMinute = (seconds - nHour * 60 * 60) / 60;
        int nSecond = seconds - nHour * 60 * 60 - nMinute * 60;

        strValue = QString("%1h").arg(nHour);

        if (nMinute > 0)
            strValue += strSpacing + QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }
    else
    {
        int nDay = seconds / (60 * 60 * 24);
        int nHour = (seconds - nDay * 60 * 60 * 24) / (60 * 60);
        int nMinute = (seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60) / 60;
        int nSecond = seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60 - nMinute * 60;

        strValue = QString("%1d").arg(nDay);

        if (nHour > 0)
            strValue += strSpacing + QString("%1h").arg(nHour);

        if (nMinute > 0)
            strValue += strSpacing + QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }

    return strValue;
}

char *MyHelper::Wchar_tToString(wchar_t *wchar)
{
    wchar_t * wText = wchar;
    DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wText,-1,NULL,0,NULL,FALSE);// WideCharToMultiByte的运用
    char *psText; // psText为char*的临时数组，作为赋值给std::string的中间变量
    psText = new char[dwNum];
    WideCharToMultiByte (CP_OEMCP,NULL,wText,-1,psText,dwNum,NULL,FALSE);// WideCharToMultiByte的再次运用
    //szDst = psText;// std::string赋值
    //delete []psText;// psText的清除
    return  psText;
}

DWORD MyHelper::GetProcessidFromName(const char *name)
{
    PROCESSENTRY32 pe;
    DWORD id=0;
    HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    pe.dwSize=sizeof(PROCESSENTRY32);
    if(!Process32First(hSnapshot,&pe))
        return 0;
    while(1)
    {
        pe.dwSize=sizeof(PROCESSENTRY32);
        if(Process32Next(hSnapshot,&pe)==FALSE)
            break;
        if(strcmp((Wchar_tToString(pe.szExeFile)),name)==0)
        {
            id=pe.th32ProcessID;

            break;
        }

    }
    CloseHandle(hSnapshot);
    return id;
}

WINBOOL MyHelper::KillProcess(DWORD ProcessId)
{
    HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,ProcessId);
    if(hProcess==NULL)
        return FALSE;
    if(!TerminateProcess(hProcess,0))
        return FALSE;
    return TRUE;
}

bool MyHelper::ExistPath()
{

    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\DataManageTools.exe",QSettings::NativeFormat);
    QString value = settings.value("value", "error").toString();//读
     if(!value.isEmpty())
         return true;
     return  false;
}

QString MyHelper::GetPath(bool is_folder)
{
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\DataManageTools.exe",QSettings::NativeFormat);
    QString value = settings.value("value").toString();//读

    if (is_folder)
    {
       // return QDir::filePath(value);
        QFileInfo f(value);
        return  f.dir().path();
    }

    return value;

}

bool MyHelper::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
    //复制配置文件
       toDir.replace("\\","/");
       if (sourceDir == toDir){
           return true;
       }
       if (!QFile::exists(sourceDir)){
           return false;
       }
       QDir *createfile     = new QDir;
       bool exist = createfile->exists(toDir);
       if (exist){
           if(coverFileIfExist){
               createfile->remove(toDir);
           }
       }//end if

       if(!QFile::copy(sourceDir, toDir))
       {
           return false;
       }
       return true;
}

bool MyHelper::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{

}

QString MyHelper::exeVersion(const QString &exePath)
{
    QFileInfo fileInfo(exePath);
    if (!fileInfo.exists())
        return "";

    DWORD dwHandle;
    DWORD dwLen = GetFileVersionInfoSize(exePath.toStdWString().c_str(), &dwHandle);

    LPVOID lpData = new BYTE[dwLen];
    if(!GetFileVersionInfo(exePath.toStdWString().c_str(), dwHandle, dwLen, lpData))
    {
        delete[] lpData;
        return "";
    }

    VS_FIXEDFILEINFO *lpBuffer = NULL;
    UINT uLen;
    if(!VerQueryValue(lpData,
                      QString("\\").toStdWString().c_str(),
                      (LPVOID*)&lpBuffer,
                      &uLen))
    {
        delete[] lpData;

        return "";
    }

    return QString::number((lpBuffer->dwFileVersionMS >> 16) & 0xffff) + "." +
            QString::number((lpBuffer->dwFileVersionMS) & 0xffff) + "." +
            QString::number((lpBuffer->dwFileVersionLS >> 16) & 0xffff) + "." +
            QString::number((lpBuffer->dwFileVersionLS) & 0xffff);
}

int MyHelper::Compress(char *pSrcFile, char *pDstFile)
{

    return  LzmaCompress(pSrcFile,  pDstFile);
}

int MyHelper::Uncompress(char *pSrcFile, char *pDstFile)
{
    return LzmaUncompress(pSrcFile,  pDstFile);
}

QString XMLHelper::GetNodeValue(const QString &nodename)
{

    //loadfile();

    if(FilePath.isEmpty())
        FilePath="Update.xml";
    QString strFile(FilePath);
    QFile file(strFile);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {  // 以只读模式打开
        qDebug() << QString("Cannot read file %1(%2).").arg(strFile).arg(file.errorString());
        return "error " ;
    }
    xml.setDevice(&file);

    if(xml.readNextStartElement())
    {
        QString elename= xml.name().toString() ;
        Q_ASSERT(xml.isStartElement() && xml.name().toString() == elename);
        while (xml.readNextStartElement())
        {
            QString myelename= xml.name().toString() ;
            if (xml.name().toString() == nodename)
            {
                Q_ASSERT(xml.isStartElement() && xml.name().toString() == nodename);
                return  xml.readElementText();
            }
            else
            {
                xml.skipCurrentElement();  // 跳过当前元素
            }
        }
    }
    else
    {
        return "nofind ";
    }



}

QString XMLHelper::GetAttributesValue(const QString &nodename, const QString &Attributesname)
{

    //load
    if(FilePath.isEmpty())
        FilePath="Update.xml";

    QString strFile(FilePath);
    QFile file(strFile);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {  // 以只读模式打开
        qDebug() << QString("Cannot read file %1(%2).").arg(strFile).arg(file.errorString());
        return  "error ";
    }
    xml.setDevice(&file);
    // loadfile();

    if(xml.readNextStartElement())
    {
        QString elename= xml.name().toString() ;
        Q_ASSERT(xml.isStartElement() && xml.name().toString() == elename);
        while (xml.readNextStartElement())
        {
            QString myelename= xml.name().toString() ;
            if (xml.name().toString() == nodename)
            {
                Q_ASSERT(xml.isStartElement() && xml.name().toString() == nodename);
                QXmlStreamAttributes attributes = xml.attributes();
                if (attributes.hasAttribute(Attributesname))
                {
                    return attributes.value(Attributesname).toString();
                }
                else
                {
                    xml.raiseError("XML file format error.");
                }
            }
            else
            {
                xml.skipCurrentElement();  // 跳过当前元素
            }
        }
    }
    else
    {
        return  "nofind";

    }



}

void XMLHelper::SetNodeValue(const QString &nodename, const QString &nodevalue)
{
    //load
    if(FilePath.isEmpty())
        FilePath="Update.xml";
    QString strFile(FilePath);
    QFile file(strFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << QString("Cannot read file %1(%2).").arg(strFile).arg(file.errorString());
        return;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    //update
    QDomElement root = doc.documentElement();
    // qDebug() << root.tagName();
    QDomNode node ;  // 返回根节点的第一个子节点
    /**********遍历元素 **********/
    QDomNodeList list = root.childNodes();
    for (int i = 0; i < list.count(); i++)
    {
        node = list.at(i);
        if (node.isElement())
        {
            if( nodename==node.nodeName())
            {
                //node.setNodeValue(nodevalue);
                QDomNode oldnode = node.firstChild();     //标签之间的内容作为节点的子节点出现，得到原来的子节点
                node.firstChild().setNodeValue(nodevalue);   //用提供的value值来设置子节点的内容
                QDomNode newnode = node.firstChild();     //值修改过后
                node.replaceChild(newnode,oldnode);      //调用节点的replaceChild方法实现修改功能

            }
        }
    }
//save
    QFile filexml(strFile);
    if( !filexml.open( QFile::WriteOnly | QFile::Truncate) )
    {
        qWarning("error::ParserXML->writeOperateXml->file.open\n");
        // return false;

    }
    QTextStream ts(&filexml);
    ts.reset();
    ts.setCodec("utf-8");
    doc.save(ts, 4, QDomNode::EncodingFromTextStream);
    filexml.close();

}

void XMLHelper::SetAttributesValue(const QString &nodename, const QString &Attributesname, const QString &Attributevalue)
{
    //load
    if(FilePath.isEmpty())
        FilePath="Update.xml";
    QString strFile(FilePath);
    QFile file(strFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << QString("Cannot read file %1(%2).").arg(strFile).arg(file.errorString());
        return;
    }

    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    //update
    QDomElement root = doc.documentElement();
    // qDebug() << root.tagName();
    QDomNode node ;  // 返回根节点的第一个子节点

    /**********遍历元素 **********/
    QDomNodeList list = root.childNodes();
    for (int i = 0; i < list.count(); i++)
    {
        node = list.at(i);

        if (node.isElement())
        {

            if( nodename==node.nodeName())
            {
                node.toElement().setAttribute(Attributesname,Attributevalue);

            }
        }
    }

    QFile filexml(strFile);
    if( !filexml.open( QFile::WriteOnly | QFile::Truncate) )
    {
        qWarning("error::ParserXML->writeOperateXml->file.open\n");
        // return false;

    }
    QTextStream ts(&filexml);
    ts.reset();
    ts.setCodec("utf-8");
    doc.save(ts, 4, QDomNode::EncodingFromTextStream);
    filexml.close();


}

QString XMLHelper::errorString() const
{
    return QString("Error:%1  Line:%2  Column:%3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}

void XMLHelper::loadfile()
{
    if(FilePath.isEmpty())
        FilePath="Update.xml";

    QString strFile(FilePath);
    QFile file(strFile);
    if (!file.open(QFile::ReadOnly| QFile::Text))
    {  // 以只读模式打开
        qDebug() << QString("Cannot read file %1(%2).").arg(strFile).arg(file.errorString());
        return  ;
    }

    //
    xml.setDevice(&file);

    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }


}



// 生成RSA密钥对
void RSAHelper::GenerateRSAKey(unsigned int keyLength, const char *privFilename, const char *pubFilename, const char *seed)
{
    RandomPool randPool;

    randPool.Put((byte *)seed, strlen(seed));
    RSAES_OAEP_SHA_Decryptor priv(randPool, keyLength);

    HexEncoder privFile(new FileSink(privFilename));

    priv.DEREncode(privFile);

    privFile.MessageEnd();
    RSAES_OAEP_SHA_Encryptor pub(priv);

    HexEncoder pubFile(new FileSink(pubFilename));
    pub.DEREncode(pubFile);
    pubFile.MessageEnd();
}

// RSA加密
QString RSAHelper::RSAEncryptString(const char *pubFilename, const char *seed, const char *message)
{

        FileSource pubFile(pubFilename, true, new HexDecoder);

        RSAES_OAEP_SHA_Encryptor pub(pubFile);

        RandomPool randPool;

        randPool.Put((byte *)seed, strlen(seed));

        string result;


        StringSource(message, true, new PK_EncryptorFilter(randPool, pub, new HexEncoder(new StringSink(result))));

        return  QString(result.c_str());
}

// RSA解密
QString RSAHelper::RSADecryptString(const char *privFilename, const char *ciphertext)
{
       FileSource privFile(privFilename, true, new HexDecoder);

         RSAES_OAEP_SHA_Decryptor priv(privFile);

         string result;

         StringSource(ciphertext, true, new HexDecoder(new PK_DecryptorFilter(GlobalRNG(), priv, new StringSink(result))));

         return QString(result.c_str());
}

// 定义全局的随机数池
RandomPool & RSAHelper::GlobalRNG()
{
    static RandomPool randomPool;
          return randomPool;
}


MqttHelper::MqttHelper(QObject *parent):QObject(parent)
{
     _number=0;
      _client = new QMQTT::Client(QHostAddress::LocalHost, 1883);
   _Subscriber= new QMQTT::Client(QHostAddress::LocalHost, 1883);


   connect(_client,_client->connected, this, &MqttHelper::Subscribe);
   connect(&_timer, &QTimer::timeout, this, &MqttHelper::onTimeout);
   connect(_client, _client->disconnected, this, &MqttHelper::onDisconnected);

   connect(_Subscriber, _Subscriber->connected, this, &MqttHelper::Subscribe);
   connect(_Subscriber, _Subscriber->subscribed, this, &MqttHelper::onSubscribed);
   connect(_Subscriber, _Subscriber->received, this, &MqttHelper::onReceived);
   Connect();

}

void MqttHelper::Connect()
{
     //  _client->setClientId("client_id_1");
     //  _client->setUsername("sagarfan");
     //  _client->setPassword("password");
       _client->connectToHost();
       _Subscriber->connectToHost();

       qDebug()<<"_client connet"<<_client->isConnectedToHost();
       qDebug()<<"_Subscriber connet"<< _Subscriber->isConnectedToHost();
       //if (_client->isConnectedToHost()&&_Subscriber->isConnectedToHost())
           qDebug()<<"connet ";

}

void MqttHelper::Subscribe()
{
    _client->subscribe("qmqtt/exampletopic", 0);
    _timer.start(1000);
   _Subscriber->subscribe("qmqtt/exampletopic", 0);
   qDebug()<<"Subscribe";

}

void MqttHelper::publish()
{
    QString payload = "{\"cmd\":1}";
    qDebug() << payload;
    QMQTT::Message msg(0,"cmd",payload.toLatin1());
    if(_client->isConnectedToHost())
    {
        _client->publish(msg);
    }
    else
    {
        qDebug() << "not connected";
    }
}

void MqttHelper::MqttMsgSubscribed()
{

}

QString MqttHelper::MqttMsgPublishReceived()
{

}

void MqttHelper::ConnectionClosed()
{
       if (_client->isConnectedToHost())
       {
           _client->disconnectFromHost();

       }
       if (_Subscriber->isConnectedToHost())
       {
          _Subscriber->disconnectFromHost();

       }
}

void MqttHelper::onTimeout()
{
    QMQTT::Message message(_number, "qmqtt/exampletopic",
                           QString("Number is %1").arg(_number).toUtf8());
   _client->publish(message);
    _number++;
    if(_number >= 10)
    {
        _timer.stop();
       // disconnectFromHost();
    }
}

void MqttHelper::onDisconnected()
{
    QTimer::singleShot(0, qApp, &QCoreApplication::quit);
}

void MqttHelper::onSubscribed(const QString &topic)
{
    qDebug()<< "subscribed " << topic << endl;
}

void MqttHelper::onReceived(const QMQTT::Message &message)
{
   qDebug() << "publish received: \"" << QString::fromUtf8(message.payload());

}
