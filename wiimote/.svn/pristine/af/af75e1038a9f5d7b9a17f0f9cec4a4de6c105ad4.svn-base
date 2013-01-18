/*
 ============================================================================
 Name		: DeviceFinder.h
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CDeviceFinder declaration
 ============================================================================
 */

#ifndef DEVICEFINDER_H
#define DEVICEFINDER_H

#include <e32base.h>
#include <e32std.h>
#include <es_sock.h>
#include <bt_sock.h>
#include <btextnotifiers.h>
#include "MBlueWiimoteObserver.h"

class CDeviceFinder : public CActive
    {
public:
    ~CDeviceFinder();

    static CDeviceFinder* NewL(MBlueWiimoteObserver& aObserver);

    static CDeviceFinder* NewLC(MBlueWiimoteObserver& aObserver);

    void StartDiscoverL();
            
private:
    CDeviceFinder(MBlueWiimoteObserver& aObserver);

    void ConstructL();

    void RunL();

    void DoCancel();

    TInt RunError(TInt aError);

private:
    enum TDeviceFinderState
        {
        EDiscover,
        EReady
        };

    MBlueWiimoteObserver&             iObserver;
    TInt                            iState;
    TBool                           iConnected;
    RSocketServ                     iSockServ;
    RHostResolver                   iResolver;
    RNotifier                       iNotifier;
    TBTDeviceSelectionParamsPckg    iSelParams;
    TBTDeviceResponseParamsPckg     iResParams;
    TInquirySockAddr                iAddr;
    TNameEntry                      iEntry;
    TBTDevAddr                      iBtAddr;
    };

#endif // DEVICEFINDER_H
