/*
 ============================================================================
 Name		: SocketConnect.cpp
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CSocketConnect implementation
 ============================================================================
 */

#include "SocketConnect.h"

CSocketConnect::CSocketConnect(MSocketHandlerObserver& aObserver, TInt aPort) :
    CActive(EPriorityStandard),
    iObserver(aObserver),
    iPort(aPort),
    iState(EUnconnected)
    {
    }

CSocketConnect* CSocketConnect::NewLC(MSocketHandlerObserver& aObserver, TInt aPort)
    {
    CSocketConnect* self = new (ELeave) CSocketConnect(aObserver,aPort);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CSocketConnect* CSocketConnect::NewL(MSocketHandlerObserver& aObserver, TInt aPort)
    {
    CSocketConnect* self = CSocketConnect::NewLC(aObserver,aPort);
    CleanupStack::Pop();
    return self;
    }

void CSocketConnect::ConstructL()
    {    
    CActiveScheduler::Add(this);
    User::LeaveIfError(iSockServ.Connect());
    iConnected = EFalse;
    }

CSocketConnect::~CSocketConnect()
    {
    Cancel();

    iSocket.Close();
    }

void CSocketConnect::DoCancel()
    {
    iSocket.CancelAll();
    }

void CSocketConnect::RunL()
    {
    TInt err(0);
    err = iStatus.Int();

    if(err == KErrCancel)
        return;
    
    if(err == KErrNone && iState == EConnecting)
        {
        iConnected = ETrue;
        iObserver.SocketAccept(iSocket,iAddr.Port());
        }
    }


TInt CSocketConnect::RunError(TInt aError)
    {
    return aError;
    }

void CSocketConnect::ConnectHost(TBTDevAddr aAddr)
    {
    if(iConnected)
        return;
    
    Cancel();
    iAddr.SetPort(iPort);
    iAddr.SetBTAddr(aAddr);
    iSocket.Close();
    iSocket.Open(iSockServ,KL2CAPDesC());
    iSocket.Connect(iAddr,iStatus);
    iState = EConnecting;
    SetActive();
    }


TBool CSocketConnect::IsConnected()
    {
    return iConnected;
    }
