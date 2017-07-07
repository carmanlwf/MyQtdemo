#include "parklotupdate.h"

ParklotUpdate::ParklotUpdate()
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    if (!ExistPath())
    {
        //判断是否初次安装
        availableUpdate=false;
        return ;
    }

    //文件路径
    localinfo=readXML(true);

    //初始化参数
    XMLHelper xml;
    xml.FilePath=localinfo;
    inisialized =xml.GetNodeValue("Inisialized").toInt();

    if(0==inisialized)
    {
        availableUpdate=false;
        qDebug()<<"未初始化";
        return ;
    }
    infoUrl=xml.GetNodeValue("InfoUrl");
    downloadUrl=xml.GetNodeValue("DownloadUrl");
    current_version=xml.GetAttributesValue("File","version_code");
    //获取服务器参数
    DownloadFile(infoUrl);
    //比对参数
    availableUpdate=checkinfo(localinfo,serverinfomap);

    /*
    if(availableUpdate)
    {
        //下载
        DownloadFile(downloadUrl);
    }
 */
}

void ParklotUpdate::DownloadFile(const QString &url)
{

    // url.append("DataManageToolsSetup.msi");
    // URL
    //  QString baseUrl = "http://120.24.249.69/parkhero/v0.1/appman/version?package_name=DataManageToolsSetup.msi";
    qDebug()<<"发送版本信息请求";
    m_url= QUrl(url);
    // 构造请求
    m_req.setUrl(m_url);
    //  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 发送请求
    m_pReply= manager->get(m_req);
    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    // 获取响应信息
    QByteArray bytes = m_pReply->readAll();
    //qDebug() << "recv"<<bytes;
    RecvJson(bytes);

}

void ParklotUpdate::UpdateXML()
{

    qDebug()<<"更新xml配置";
    XMLHelper xml;
    xml.FilePath=localinfo;

    // xml.SetNodeValue("File",);
    //更新xml配置
    xml.SetAttributesValue("File","version_code",serverinfomap.value("version_code"));
    xml.SetAttributesValue("File","release_date",serverinfomap.value("release_date"));
}

bool ParklotUpdate::ExistPath()
{

    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\DataManageTools.exe",QSettings::NativeFormat);
    QString value = settings.value("value").toString();//读

    if(!value.isEmpty())
    {
        return true;
    }
    else
    {
        qDebug()<<" 程序未安装";
        return  false;
    }
}

QString ParklotUpdate::readXML(bool o)
{
    return  QString("Update.xml");
}

bool ParklotUpdate::checkinfo(const QString &localinfo, const QMap<QString, QString> &)
{
    qDebug()<<"配置信息比对";
    if (!QFile(localinfo).exists()|| serverinfomap.isEmpty())
    {
        qDebug()<<"配置信息错误不能比对";
        return  false ;
    }

    QString localupdatetime,serverupdatetime ;
    XMLHelper  xml;
    xml.FilePath=localinfo;

    localupdatetime= xml.GetAttributesValue("File","version_code");
    serverupdatetime=serverinfomap.value("version_code");

    if (localupdatetime < serverupdatetime)
    {
        qDebug()<<"需要更新";
        return true;
    }

    return  false ;
}

void ParklotUpdate::CreateDirtory(const QString &path)
{
     qDebug()<<path;
}

bool ParklotUpdate::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{

    qDebug()<<"复制配置文件";
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

bool ParklotUpdate::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir())
        {    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                   targetDir.filePath(fileInfo.fileName()),
                                   coverFileIfExist))
                return false;
        }
        else
        {            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                            targetDir.filePath(fileInfo.fileName()))){
                return false;
            }
        }
    }
    return true;
}

void ParklotUpdate::Uninstallser()
{

    qDebug()<<"执行卸载程序";
    qDebug()<<"downfilepath"<<downfilepath;
    QStringList arguments;
    arguments << "/c "<<"msiexec"<<"/x"<< "{6F493981-FB85-4282-8BAF-F9373FE83F92}"<<"/qn";

    if ( !comand(arguments))
    {
        qDebug()<<"failed exec commad";
    }

}

void ParklotUpdate::Installser()
{
    /*
    QString path=MyHelper::GetPath(true);

    path +="/myInstall.bat";
    path.replace("/","\\");
    qDebug()<<"path"<<path;
    */
    qDebug()<<"执行安装程序";
    qDebug()<<"downfilepath"<<downfilepath;
    QString path = downfilepath;
    path.replace("/","\\");

     qDebug()<<path;
    QStringList arguments;
    arguments << "/c "<<"msiexec"<<"/i"<< path<<"/qn";

    qDebug()<<"arguments"<<arguments;
    if ( !comand(arguments))
    {
        qDebug()<<"failed exec commad";
    }
}

bool ParklotUpdate::HasInstallSuccess()
{

    qDebug()<<"判断程序安装结果";
    QString current_version, new_version;
    current_version=MyHelper::exeVersion(MyHelper::GetPath(false));
    new_version=serverinfomap.value("version_name");

    if( current_version<new_version)
        return  false;

    return true;



}

void ParklotUpdate::DownUpdateFile()
{
    qDebug()<<"下载更新文件";
    execute();

}

void ParklotUpdate::RecvJson(const QByteArray &byteArray)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        if (doucment.isObject())
        {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("kind")) {
                QJsonValue value = object.value("kind");
                if (value.isString()) {
                    QString strName = value.toString();
                    serverinfomap.insert("kind",strName);
                    qDebug() << "kind : " << strName;
                }
            }
            if (object.contains("package_name")) {
                QJsonValue value = object.value("package_name");
                if (value.isString()) {
                    QString strCompany = value.toString();
                    serverinfomap.insert("package_name",strCompany);
                    qDebug() << "package_name : " << strCompany;
                }
            }
            if (object.contains("filename")) {
                QJsonValue value = object.value("filename");
                if (value.isString()) {
                    QString nFrom = value.toString();
                    serverinfomap.insert("filename",nFrom);
                    file_name=nFrom;
                    qDebug() << "filename : " << nFrom;
                }
            }
            if (object.contains("version_code"))
            {
                QJsonValue value = object.value("version_code");
                /*
                if (value.isString())
                {
                    QString nFrom = value.toString();
                    serverinfomap.insert("version_code",nFrom);
                    qDebug() << "version_code : " << nFrom;
                }*/
                if (value.isDouble()) {
                    int   strDownload = value.toInt();
                    serverinfomap.insert("version_code",QString::number(strDownload));
                    qDebug() << "version_code : " << strDownload;
                }
            }
            if (object.contains("release_notes"))
            {
                QJsonValue value = object.value("release_notes");
                if (value.isString())
                {
                    QString nFrom = value.toString();
                    serverinfomap.insert("release_notes",nFrom);
                    qDebug() << "release_notes : " << nFrom;
                }
            }
            if (object.contains("version_name"))
            {
                QJsonValue value = object.value("version_name");
                if (value.isString())
                {
                    QString nFrom = value.toString();
                    serverinfomap.insert("version_name",nFrom);
                    new_version =nFrom;
                    qDebug() << "version_name : " << nFrom;
                }
            }

            if (object.contains("status"))
            {
                QJsonValue value = object.value("status");
                /*
                if (value.isString()) {
                    QString strDownload = value.toString();
                    qDebug() << "status : " << strDownload;
                }*/
                if (value.isDouble()) {
                    int   strDownload = value.toInt();
                    serverinfomap.insert("status",QString::number(strDownload));
                    qDebug() << "status : " << strDownload;
                }
            }
            if (object.contains("release_date"))
            {
                QJsonValue value = object.value("release_date");
                if (value.isString()) {
                    QString strDevelopers = value.toString();
                    serverinfomap.insert("release_date",strDevelopers);
                    qDebug() << "release_date : " << strDevelopers;
                }
            }


        }
    }
}

bool ParklotUpdate::comand(const QStringList &args)
{
    QProcess p;
    p.start("cmd.exe",args);
    if (p.waitForStarted())
    {
        p.waitForFinished();
        // qDebug() <<QString::fromLocal8Bit(p.readAllStandardOutput());
        return true;
    }
    else
    {
        // qDebug() << "Failed to start Install";
        return  false;
    }
}



void ParklotUpdate::execute()
{
    qDebug()<<"发送下载更新文件请求";
    QString myurl;

    // 获取当前的时间戳，设置下载的临时文件名称
    QDateTime dateTime = QDateTime::currentDateTime();
    QString date = dateTime.toString("yyyy-MM-dd-hh-mm-ss-zzz");
    m_strFileName =MyHelper::GetPath(true)+ QString("/temp/%1.tmp").arg(date);

    if(!serverinfomap.value("filename").isEmpty())
        myurl=downloadUrl+serverinfomap.value("filename");

    m_url = QUrl(myurl);
    QNetworkRequest request;
    request.setUrl(m_url);
    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/zip");
    m_pReply =  manager->get(request);
    //connect(m_pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));
    connect(m_pReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void ParklotUpdate::UninstallserServer()
{
    qDebug()<<"卸载服务";
    QString path=MyHelper::GetPath(true);

    path +="/myUninstall.bat";
    path.replace("/","\\");
    qDebug()<<"path"<<path;
    QStringList arguments;
    arguments << "/c "<<path;
    if ( !comand(arguments))
    {
        qDebug()<<"failed exec commad";
    }
}

void ParklotUpdate::InstallserServer()
{
    qDebug()<<"安装服务";
    QString path=MyHelper::GetPath(true);

    path +="/myInstall.bat";
    path.replace("/","\\");
    qDebug()<<"path"<<path;
    QStringList arguments;
    arguments << "/c "<<path;

    if ( !comand(arguments))
    {
        qDebug()<<"failed exec commad";
    }
}

void ParklotUpdate::StopServer()
{

    qDebug()<<"停止服务";
    QString path=MyHelper::GetPath(true);

    path +="/myStop.bat";
    path.replace("/","\\");
    qDebug()<<"path"<<path;
    QStringList arguments;
    arguments << "/c "<<path;

    if ( !comand(arguments))
    {
        qDebug()<<"failed exec commad";
    }
}

void ParklotUpdate::replyFinished(QNetworkReply *reply)
{
    // 获取响应的信息，状态码为200表示正常
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    // 无错误返回
    if (reply->error() == QNetworkReply::NoError)
    {
        // 重命名临时文件
        QFileInfo fileInfo(m_strFileName);
        QFileInfo newFileInfo = fileInfo.absolutePath() +"/"+ m_url.fileName();
        QDir dir;
        if (dir.exists(fileInfo.absolutePath()))
        {
            //  qDebug()<<"old absolutePath"<<fileInfo.absolutePath()<<"new "<<newFileInfo.absoluteFilePath();
            if (newFileInfo.exists())
                newFileInfo.dir().remove(newFileInfo.fileName());
            QFile::rename(m_strFileName, newFileInfo.absoluteFilePath());
            downfilepath=newFileInfo.absoluteFilePath();
            qDebug()<<"完成下载文件";
        }
    }
    else
    {
        QString strError = reply->errorString();
        qDebug() << "Error:" << strError;
    }

    //   emit replyFinished(statusCode.toInt());
}

void ParklotUpdate::readyRead()
{
    /*
    QFileInfo fileInfo(m_strFileName);
    QFileInfo newFileInfo = fileInfo.absolutePath() + m_url.fileName();
    QString strFileName = newFileInfo.absoluteFilePath();
     */
    // emit fileName(strFileName);
    // 写文件-形式为追加
    qDebug()<<"接收下载更新文件";
    QFile file(m_strFileName);
    if (file.open(QIODevice::Append))
        file.write(m_pReply->readAll());
    file.close();
}
