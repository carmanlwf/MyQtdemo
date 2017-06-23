#ifndef PARKLOT_H
#define PARKLOT_H

#include <QObject>

class Parklot
{
public:
    Parklot();

  // void Connect(MqttClient client);
  // void Disconnect(MqttClient client);
  // void  Update(UpdateInfo);
  // void DoAction(actionname);
   void SendMail();

    QString UpdateInfo,ParkInfo,ConnectInfo;
};

#endif // PARKLOT_H
