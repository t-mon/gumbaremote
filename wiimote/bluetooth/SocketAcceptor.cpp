/*
 ============================================================================
 Name		: SocketAcceptor.cpp
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CSocketAcceptor implementation
 ============================================================================
 */

#include "SocketAcceptor.h"
#include "common.h"

CSocketAcceptor::CSocketAcceptor(MSocketHandlerObserver& aObserver, TInt aPort) :
    CActive(EPriorityStandard),
    iObserver(aObserver),
    iPort(aPort)
    {
    }

CSocketAcceptor* CSocketAcceptor::NewLC(MSocketHandlerObserver& aObserver, TInt aPort)
    {
    CSocketAcceptor* self = new (ELeave) CSocketAcceptor(aObserver,aPort);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CSocketAcceptor* CSocketAcceptor::NewL(MSocketHandlerObserver& aObserver, TInt aPort)
    {
    CSocketAcceptor* self = CSocketAcceptor::NewLC(aObserver,aPort);
    CleanupStack::Pop();
    return self;
    }

void CSocketAcceptor::ConstructL()
    {    
    CActiveScheduler::Add(this);
    User::LeaveIfError(iSockServ.Connect());
    User::LeaveIfError(iListeningSocket.Open(iSockServ, KL2CAPDesC()));
    
    TL2CAPSockAddr addr;
    addr.SetPort(iPort);
    TBTServiceSecurity serverSecurity;
    serverSecurity.SetUid(KAppUid);
    serverSecurity.SetAuthentication(EFalse);
    serverSecurity.SetAuthorisation(EFalse);
    serverSecurity.SetDenied(EFalse);
    serverSecurity.SetEncryption(ETrue);
    
    if (KInterruptChannel == iPort)
        {        
        serverSecurity.SetEncryption(EFalse);
        }

    addr.SetSecurity(serverSecurity);
    
    //Bind
    iListeningSocket.Bind(addr);
    iListeningSocket.Listen(1);
      
    iConnected = EFalse;
    }

CSocketAcceptor::~CSocketAcceptor()
    {
    Cancel();
    iAcceptedSocket.Close();
    iListeningSocket.Close();    
    iSockServ.Close();
    }

void CSocketAcceptor::DoCancel()
    {
    iAcceptedSocket.CancelAll();
    iListeningSocket.CancelAccept();    
    }

TInt CSocketAcceptor::StartListeningL()
    {
    TInt err(0);
    iAcceptedSocket.Close();
    err = iAcceptedSocket.Open(iSockServ);
    
    if(err == KErrNone)
        {
        iListeningSocket.Accept(iAcceptedSocket,iStatus);        
        SetActive();
        }
    return err;
    }

void CSocketAcceptor::RunL()
    {
    TInt err(0);
    err = iStatus.Int();
    
    if(err == KErrCancel)
        return;

    if(err == KErrNone)
        {
        iConnected = ETrue;
        iObserver.SocketAccept(iAcceptedSocket,iPort);
        iListeningSocket.CancelAccept();
        }
    }

TInt CSocketAcceptor::RunError(TInt aError)
    {
    return aError;
    }

TBool CSocketAcceptor::IsConnected()
    {
    return iConnected;
    }
