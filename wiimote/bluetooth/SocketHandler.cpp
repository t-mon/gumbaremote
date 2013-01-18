/*
 ============================================================================
 Name		: CSocketHandler.cpp
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CSocketHandler implementation
 ============================================================================
 */

#include "SocketHandler.h"
#include "common.h"
#include <QByteArray>;
#include <QDebug>

CSocketHandler::CSocketHandler(MBlueWiimoteObserver& aObserver) :
    CActive(EPriorityStandard),
    iObserver(aObserver),    
    iDataPtr(0,0)
{

}

CSocketHandler* CSocketHandler::NewLC(MBlueWiimoteObserver& aObserver)
    {
    CSocketHandler* self = new (ELeave) CSocketHandler(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CSocketHandler* CSocketHandler::NewL(MBlueWiimoteObserver& aObserver)
    {
    CSocketHandler* self = CSocketHandler::NewLC(aObserver);
    CleanupStack::Pop();
    return self;
    }

void CSocketHandler::ConstructL()
{
    CActiveScheduler::Add(this);
    iData = (TUint8*)User::AllocL(KDataSize);
    iDataPtr.Set(iData,KDataSize,KDataSize);
    iDataPtr.Zero();
    iConnectState = EUnconnected;
    
        
    User::LeaveIfError(iSockServ.Connect());
    iControlAcceptor = CSocketAcceptor::NewL(*this,KControlChannel);
    iInterruptAcceptor = CSocketAcceptor::NewL(*this,KInterruptChannel);
    iControlConnect = CSocketConnect::NewL(*this,KControlChannel);
    iInterruptConnect = CSocketConnect::NewL(*this,KInterruptChannel);
}

CSocketHandler::~CSocketHandler()
{
    Cancel();
    if(IsConnected())
        {
        TRAPD(err,DisconnectHost());
        }
    if(iControlConnect)
        {
        delete iControlConnect;
        iControlConnect = NULL;
        }
    if(iInterruptConnect)
        {
        delete iInterruptConnect;
        iInterruptConnect = NULL;
        }    
    if(iInterruptAcceptor)
        {
        delete iInterruptAcceptor;
        iInterruptAcceptor = NULL;
        }
    if(iControlAcceptor)
        {
        delete iControlAcceptor;
        iControlAcceptor = NULL;
        }
    if(iData)
        {
        User::Free(iData);
        iData = NULL;
        }
    
    iSockServ.Close();
}

void CSocketHandler::DoCancel()
{
    iInterrupt.CancelAll();
    iControl.CancelAll();
    iDataPtr.Zero();
}


void CSocketHandler::RunL()
{
    TInt err(0);
    err = iStatus.Int();
    
    if(err == KErrCancel)
        return;

    if(err != KErrNone)
    {        
        iObserver.Disconnected();
    }

    switch(iState)
    {
        case EReceiving:
        {
            //CheckData();
        qDebug() << "EReceiving:"<< QString::number(iDataPtr.Length());
            QByteArray buffer(reinterpret_cast<const char*>(iDataPtr.Ptr()), iDataPtr.Length());
            iObserver.Receiving(buffer);
            Receive();
        }break;

        case ESending:
        {
            iObserver.Sending();
            Receive();
        }break;

        default: break;
    }
}

TInt CSocketHandler::RunError(TInt aError)
{
    return aError;
}

void CSocketHandler::StartListeningL()
{
    iControlAcceptor->Cancel();
    iControlAcceptor->StartListeningL();
    iInterruptAcceptor->Cancel();
    iInterruptAcceptor->StartListeningL();
}


void CSocketHandler::Receive()
{
    iDataPtr.Zero();
    iState = EReceiving;
    iInterrupt.Read(iDataPtr,iStatus);
    SetActive();
}

void CSocketHandler::SendDataL(const TDesC8& aData)
{
    if(!IsConnected())
        return;
    
    if(IsActive())
        Cancel();
    
    TInt len(aData.Length());
    TUint8* data = (TUint8*)User::AllocLC(len);
    TPtr8 ptr(data,len,len);
    ptr.Copy(aData);

    iInterrupt.Write(ptr,iStatus);
    CleanupStack::PopAndDestroy(data);
    
    iState = ESending;
    SetActive();        
}

void CSocketHandler::DisconnectHost()
{
    // send VIRTUAL_CABLE_UNPLUG first, then close sockets    
    if(IsConnected())
        {
        iObserver.Disconnected();
        Cancel();
        
        TRequestStatus stat;
        TUint8* data = (TUint8*)User::AllocLC(1);
        TPtr8 ptr(0,0);
        ptr.Set(data,1,1);
        ptr[0] = 0x05;
        TRAPD(err,iInterrupt.Write(ptr,stat));                
        User::WaitForRequest(stat);
        iInterrupt.Close();
        
        TRAPD(cont_err,iControl.Write(ptr,stat));
        User::WaitForRequest(stat);
        iControl.Close();
        CleanupStack::PopAndDestroy(data);
        iConnectState = EUnconnected;
        
        StartListeningL();
        }
}

void CSocketHandler::ConnectHost(TBTDevAddr aAddr)
{
    if(IsConnected())
        return;

    Cancel();
    
    iInterruptAcceptor->Cancel();
    iControlAcceptor->Cancel();

    iControlConnect->ConnectHost(aAddr);
    iInterruptConnect->ConnectHost(aAddr);
}

TBool CSocketHandler::IsConnected()
{
    if(iConnectState == EUnconnected)
        return EFalse;
    else
        return ETrue;
}

void CSocketHandler::SocketAccept(RSocket aSocket, TInt aPort)
{
    switch(aPort)
        {
        case KControlChannel:
            {            
            iControl = aSocket;            
            }break;
        case KInterruptChannel:
            {
            iInterrupt = aSocket;
            Receive();
            }break;
        default:
            break;
        }
    
    if(iInterruptAcceptor->IsConnected() && iControlAcceptor->IsConnected())
        {
        iConnectState = EHostConnected;
        iObserver.Connected();
        }
    if(iControlConnect->IsConnected() && iInterruptConnect->IsConnected())
        {
        iConnectState = EClientConnected;
        iObserver.Connected();        
        }
}
