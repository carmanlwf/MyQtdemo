#ifndef PARKLOTUPDATE_H
#define PARKLOTUPDATE_H

#include <QObject>

class ParklotUpdate
{
public:
    ParklotUpdate();

 void   CheckNew(const QString&url);
  void  DownloadFile(const QString&url);
  void  Update();

  QString  UpdateInfo;
};

#endif // PARKLOTUPDATE_H
