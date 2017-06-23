

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QDateTime>
#include <QStringList>
#include <QDir>
#include <QSettings>
#include <QProcess>
#include "qtservice.h"

class HttpDaemon : public QTcpServer
{
    Q_OBJECT
public:
    HttpDaemon(quint16 port, QObject* parent = 0)
        : QTcpServer(parent), disabled(false)
    {
        listen(QHostAddress::Any, port);
    }

    void incomingConnection(int socket)
    {
        if (disabled)
            return;

        // When a new client connects, the server constructs a QTcpSocket and all
        // communication with the client is done over this QTcpSocket. QTcpSocket
        // works asynchronously, this means that all the communication is done
        // in the two slots readClient() and discardClient().
        QTcpSocket* s = new QTcpSocket(this);
        connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
        connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
        s->setSocketDescriptor(socket);

        QtServiceBase::instance()->logMessage("New Connection");
    }

    void pause()
    {
        disabled = true;
    }

    void resume()
    {
        disabled = false;
    }

private slots:
    void readClient()
    {
        if (disabled)
            return;

        // This slot is called when the client sent data to the server. The
        // server looks if it was a get request and sends a very simple HTML
        // document back.
        QTcpSocket* socket = (QTcpSocket*)sender();
        if (socket->canReadLine()) {
            QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
            if (tokens[0] == "GET") {
                QTextStream os(socket);
                os.setAutoDetectUnicode(true);
                os << "HTTP/1.0 200 Ok\r\n"
                    "Content-Type: text/html; charset=\"utf-8\"\r\n"
                    "\r\n"
                    "<h1>Nothing to see here</h1>\n"
                    << QDateTime::currentDateTime().toString() << "\n";
                socket->close();

                QtServiceBase::instance()->logMessage("Wrote to client");

                if (socket->state() == QTcpSocket::UnconnectedState) {
                    delete socket;
                    QtServiceBase::instance()->logMessage("Connection closed");
                }
            }
        }
    }
    void discardClient()
    {
        QTcpSocket* socket = (QTcpSocket*)sender();
        socket->deleteLater();

        QtServiceBase::instance()->logMessage("Connection closed");
    }

private:
    bool disabled;
};

class HttpService : public QtService<QCoreApplication>
{
  //  Q_OBJECT
public:
    HttpService(int argc, char **argv)
    : QtService<QCoreApplication>(argc, argv, "DataManageToolsService")
    {
        setServiceDescription("A dummy HTTP service implemented with Qt");
        setServiceFlags(QtServiceBase::CanBeSuspended);


    }

protected:
    void start()
    {
        QCoreApplication *app = application();

#if QT_VERSION < 0x040100
        quint16 port = (app->argc() > 1) ?
                QString::fromLocal8Bit(app->argv()[1]).toUShort() : 8080;
#else
        const QStringList arguments = QCoreApplication::arguments();
        quint16 port = (arguments.size() > 1) ?
                arguments.at(1).toUShort() : 8080;
#endif
        daemon = new HttpDaemon(port, app);

        if (!daemon->isListening()) {
            logMessage(QString("Failed to bind to port %1").arg(daemon->serverPort()), QtServiceBase::Error);
            app->quit();
        }


        //


    }

    void pause()
    {
    daemon->pause();
    }

    void resume()
    {
    daemon->resume();
    }

/*
     void ThreadAction()
            {
                checknew = Environment.TickCount;
                keepalive = Environment.TickCount;
                while (!isstop)
                {
                    //判断进程是否假死或已关闭

                    MyProcesses = Process.GetProcessesByName(appplicationname);
                    if (MyProcesses[0].HasExited)
                    {   //重启应用
                        RestartApplication();
                    }
                       //定时检查更新
                    if (Environment.TickCount - checknew > 10 * 60 * 1000) // 10分钟检查一次
                    {
                        //1、监听是否需要更新
                        CheckUpdate cu = new CheckUpdate();
                        logstring += System.DateTime.Now.ToString() + "\r\n软件版本：" + cu.new_version + "\r\n\r\n";

                        if (cu.availableUpdate)
                        {
                            find_update = true;
                            try
                            {
                                // 终止应用程序进程
                                foreach (Process myprocess in MyProcesses)
                                {
                                    if (myprocess.ProcessName == appplicationname)
                                    {
                                        myprocess.Kill(); // 终止进程
                                    }
                                }

                                // 开始更新
                                DownloadFile df = new DownloadFile(cu.updaterXmlFiles, cu.downloadUrl, cu.serverinfo, cu.localinfo);
                                df.DownloadFile_Shown();
                            }
                            catch { }
                        }
                        else
                        {
                            find_update = false;
                        }
                        checknew = Environment.TickCount; // 重置

                    }

                    // 2、监听上传工具是否运行
                    if (!find_update)
                    {
                        if (!ReadMessage() && Environment.TickCount - keepalive > 1 * 60 * 1000) // 返回消息未更新，且心跳超时
                        {
                            // 重启上传工具
                            foreach (Process myprocess in MyProcesses)
                            {
                                if (myprocess.ProcessName == appplicationname)
                                {
                                    myprocess.Kill();
                                    myprocess.WaitForExit();
                                }
                            }

                            RestartApplication();
                            keepalive = Environment.TickCount;
                        }
                    }

                    // 不记录上传记录，仅上传前一天的日志
                    if (uploadlog < DateTime.Now.Date)
                    {
                        parkname = configxml.GetNodeValue("//parkname");
                        string topic = parkname + "(" + uploadlog.ToString("yyyyMMdd") + ")";
                        List<string> files = new List<string>();
                        string body = string.Empty;
                        string folder_servicelog = servicelogpath + "\\" + uploadlog.ToString("yyyyMMdd");
                        string folder_log = logpath + "\\" + uploadlog.ToString("yyyyMMdd");
                        if (Directory.Exists(folder_servicelog))
                        {
                            DirectoryInfo theFolder = new DirectoryInfo(folder_servicelog);
                            FileInfo[] fileInfo = theFolder.GetFiles();
                            foreach (FileInfo NextFile in fileInfo)  //遍历文件
                            {
                                string filename = folder_servicelog + "\\" + NextFile.Name;
                                files.Add(filename);
                            }
                        }
                        if (Directory.Exists(folder_log))
                        {
                            DirectoryInfo theFolder = new DirectoryInfo(folder_log);
                            FileInfo[] fileInfo = theFolder.GetFiles();
                            foreach (FileInfo NextFile in fileInfo)  //遍历文件
                            {
                                string filename = folder_log + "\\" + NextFile.Name;
                                files.Add(filename);
                            }
                        }
                        if (files.Count > 0)
                        {
                            string result = SendMail.sendMail(topic, files, body);
                            if (result != null)
                            {
                                outputlog(DateTime.Now.ToString() + "\r\n" + result + "\r\n", logpath);
                            }
                            XMLWrite_update(updatepath, uploadlog.ToString("yyyy-MM-dd"));
                        }

                        //else
                        //    outputlog(DateTime.Now.ToString() + "\r\n不存在指定的日志文件路径！\r\n", logpath);
                        uploadlog = uploadlog.AddDays(1);
                    }

                    if (logstring != string.Empty)
                        outputlog(logstring, servicelogpath);
                    logstring = string.Empty;

                    Thread.Sleep(3000); // 间隔3s
                }

                try
                {
                    ServiceController service = new ServiceController("DataManageToolsService");
                    if (service.Status == ServiceControllerStatus.Stopped)
                    {
                        //Thread.Sleep(6 * 1000);
                        service.Start();
                    }
                }
                catch (System.Exception ex)
                {
                    logstring += System.DateTime.Now.ToString() + "\r\n" + ex.Message + "\r\n\r\n";
                }
                outputlog(logstring, logpath);
                logstring = string.Empty;
            }
*/
private:
    HttpDaemon *daemon;
};

#include "main.moc"
int main(int argc, char *argv[])
{
  //  QApplication a(argc, argv);
#if !defined(Q_OS_WIN)
    // QtService stores service settings in SystemScope, which normally require root privileges.
    // To allow testing this example as non-root, we change the directory of the SystemScope settings file.
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
    qWarning("(Example uses dummy settings file: %s/QtSoftware.conf)", QDir::tempPath().toLatin1().constData());
#endif
    HttpService service(argc, argv);


    return service.exec();
}
