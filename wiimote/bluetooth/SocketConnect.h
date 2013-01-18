/*
 ============================================================================
 Name		: SocketConnect.h
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CSocketConnect declaration
 ============================================================================
 */

#ifndef SOCKETCONNECT_H
#define SOCKETCONNECT_H

#include <e32base.h>
#include <e32std.h>
#include <bt_sock.h>
#include <es_sock.h>
#include "MSocketHandlerObserver.h"

class CSocketConnect : public CActive
    {
public:
    ~CSocketConnect();

    static CSocketConnect* NewL(MSocketHandlerObserver& aObserver, TInt aPort);

    static CSocketConnect* NewLC(MSocketHandlerObserver& aObserver, TInt aPort);
   
    void ConnectHost(TBTDevAddr aAddr);
    
    TBool IsConnected();
   
private:
    CSocketConnect(MSocketHandlerObserver& aObserver, TInt aPort);

    void ConstructL();

    void RunL();

    void DoCancel();

    TInt RunError(TInt aError);

private:
    enum TStates {
        EConnecting = 0,
        EUnconnected                
    };
    
    MSocketHandlerObserver&     iObserver;
    RSocketServ                 iSockServ;
    TInt                        iPort;
    TInt                        iState;    
    RSocket                     iSocket;
    TL2CAPSockAddr              iAddr;
    TBool                       iConnected;
    };

#endif // SOCKETCONNECT_H
