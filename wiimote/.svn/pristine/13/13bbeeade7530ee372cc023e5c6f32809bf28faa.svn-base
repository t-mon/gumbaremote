/*
 ============================================================================
 Name		: DeviceFinder.cpp
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CDeviceFinder implementation
 ============================================================================
 */

#include "DeviceFinder.h"

CDeviceFinder::CDeviceFinder(MBlueWiimoteObserver& aObserver) :
    CActive(EPriorityStandard),
    iObserver(aObserver)
{
}

CDeviceFinder* CDeviceFinder::NewLC(MBlueWiimoteObserver& aObserver)
{
    CDeviceFinder* self = new (ELeave) CDeviceFinder(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

CDeviceFinder* CDeviceFinder::NewL(MBlueWiimoteObserver& aObserver)
{
    CDeviceFinder* self = CDeviceFinder::NewLC(aObserver);
    CleanupStack::Pop();
    return self;
}

void CDeviceFinder::ConstructL()
{
    CActiveScheduler::Add(this);
    iConnected = EFalse;
    iSockServ.Connect();
}

CDeviceFinder::~CDeviceFinder()
{
    Cancel();
    iResolver.Close();
    iNotifier.Close();
    iSockServ.Close();
}

void CDeviceFinder::DoCancel()
{
    iResolver.Cancel();
    iNotifier.CancelNotifier(KDeviceSelectionNotifierUid);
}

void CDeviceFinder::RunL()
{
    switch(iState)
    {
        case EDiscover:
        {
            TBTDeviceResponseParams resp = iResParams();                        
            iConnected = EFalse;
            iNotifier.CancelNotifier(KDeviceSelectionNotifierUid);
            iNotifier.Close();
        
            if(resp.IsValidBDAddr())
            {
                iObserver.DeviceSelected(resp.BDAddr());
            }
        }break;
            
        default:
            break;
    }
}

TInt CDeviceFinder::RunError(TInt aError)
{
    return aError;
}

void CDeviceFinder::StartDiscoverL()
{
    if(!iConnected)
    {
        User::LeaveIfError(iNotifier.Connect());
        iConnected = ETrue;
    }
       
    TBTDeviceResponseParams param;
    iResParams = param;
    iNotifier.StartNotifierAndGetResponse(iStatus,KDeviceSelectionNotifierUid,iSelParams,iResParams);
    iState = EDiscover;
    SetActive();
}
