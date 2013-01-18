/*
 ============================================================================
 Name		: CSocketHandler.h
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CCSocketHandler declaration
 ============================================================================
 */

#ifndef CSOCKETHANDLER_H
#define CSOCKETHANDLER_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib
#include <bt_sock.h>
#include "MBlueWiimoteObserver.h"
#include "MSocketHandlerObserver.h"
#include "SocketAcceptor.h"
#include "SocketConnect.h"

//#define MAX_LEN 36

class CSocketHandler : public CActive, MSocketHandlerObserver
    {
public:
    ~CSocketHandler();

    static CSocketHandler* NewL(MBlueWiimoteObserver& aObserver);
    
    static CSocketHandler* NewLC(MBlueWiimoteObserver& aObserver);

public:

    void StartListeningL();
    
    void DisconnectHost();
    
    void ConnectHost(TBTDevAddr aAddr);

    void SendDataL(const TDesC8& aData);
    
    TBool IsConnected();
            
protected:
    void SocketAccept(RSocket aSocket, TInt aPort);
    
private:
    CSocketHandler(MBlueWiimoteObserver& aObserver);

    void ConstructL();

    void RunL();

    void DoCancel();

    TInt RunError(TInt aError);
    
    void Receive();
        
private:
    enum TSocketHandlerState
        {        
        EReceiving,
        ESending,
        EError
        };

    enum TConnectState {
        EHostConnected,
        EClientConnected,
        EUnconnected
    };
    
private:
    MBlueWiimoteObserver&   iObserver;
    TInt                    iState;
    TInt                    iConnectState;
    CSocketAcceptor*        iControlAcceptor;
    CSocketAcceptor*        iInterruptAcceptor;
    CSocketConnect*         iControlConnect;
    CSocketConnect*         iInterruptConnect;
    RSocketServ             iSockServ;
    RSocket                 iInterrupt;
    RSocket                 iControl;

    TPtr8                   iDataPtr;
    TUint8*                 iData;
    TL2CAPSockAddr          iAddr;
    };

#endif // CSOCKETHANDLER_H
