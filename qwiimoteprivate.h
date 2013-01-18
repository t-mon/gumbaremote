#ifndef QWIIMOTEPRIVATE_H
#define QWIIMOTEPRIVATE_H

#include "btadvertiser.h"
#include "MBlueWiimoteObserver.h"
#include "SocketHandler.h"
#include "DeviceFinder.h"
#include "BTPowerControl.h"
#include "common.h"
#include "qwiimote.h"

class QWiimotePrivate : public MBlueWiimoteObserver
{
public:
    static QWiimotePrivate* NewL(QWiimote &aPublicAPI);
    virtual ~QWiimotePrivate();

    void Connect();
    void Disconnect();

    void SendData(QByteArray& buffer);

protected: // MBlueWiimoteObserver
    void Connected();
    //void AccelerometerDataReady(TInt aX, TInt aY);
    void Disconnected();
    void DeviceSelected(TBTDevAddr aAddr);
    void PowerState(TBool aOn);
    void Sending();
    void Receiving(QByteArray buffer);

private:
    void ConstructL();
    QWiimotePrivate(QWiimote &aPublicAPI);

private:
    CBTAdvertiser*         iAdvertiser;
    CSocketHandler*        iSocketHandler;
    CDeviceFinder*         iDeviceFinder;
    CBTPowerControl*       iPowerControl;
    TBlueMouseSettings     iSettings;

    QWiimote&  iPublicAPI;
};

#endif // QWIIMOTEPRIVATE_H
