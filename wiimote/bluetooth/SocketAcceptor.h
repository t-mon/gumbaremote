/*
 ============================================================================
 Name		: SocketAcceptor.h
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CSocketAcceptor declaration
 ============================================================================
 */

#ifndef SOCKETACCEPTOR_H
#define SOCKETACCEPTOR_H

#include <e32base.h>
#include <e32std.h>
#include <es_sock.h>
#include <bt_sock.h>
#include "MSocketHandlerObserver.h"

class CSocketAcceptor : public CActive
    {
public:
    ~CSocketAcceptor();

    static CSocketAcceptor* NewL(MSocketHandlerObserver& aObserver, TInt aPort);

    static CSocketAcceptor* NewLC(MSocketHandlerObserver& aObserver, TInt aPort);

    TInt StartListeningL();
    
    TBool IsConnected();
    
private:
    CSocketAcceptor(MSocketHandlerObserver& aObserver, TInt aPort);

    void ConstructL();

    void RunL();

    void DoCancel();

    TInt RunError(TInt aError);

private:
    MSocketHandlerObserver&     iObserver;
    RSocketServ                 iSockServ;
    RSocket                     iListeningSocket;
    TInt                        iPort;
    RSocket                     iAcceptedSocket;
    TBool                       iConnected;
    };

#endif // SOCKETACCEPTOR_H
