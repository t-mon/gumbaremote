/*
 ============================================================================
 Name		: BTPowerControl.cpp
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CBTPowerControl implementation
 ============================================================================
 */

#include "BTPowerControl.h"
#include <QDebug>

CBTPowerControl::CBTPowerControl(MBlueWiimoteObserver& aObserver) :
    CActive(EPriorityStandard),
    iObserver(aObserver)
{
}

CBTPowerControl* CBTPowerControl::NewLC(MBlueWiimoteObserver& aObserver)
{
    CBTPowerControl* self = new (ELeave) CBTPowerControl(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

CBTPowerControl* CBTPowerControl::NewL(MBlueWiimoteObserver& aObserver)
{
    CBTPowerControl* self = CBTPowerControl::NewLC(aObserver);
    CleanupStack::Pop();
    return self;
}

void CBTPowerControl::ConstructL()
{
    CActiveScheduler::Add(this);
}

CBTPowerControl::~CBTPowerControl()
{
    Cancel();
}

void CBTPowerControl::DoCancel()
{
    iNotifier.CancelNotifier(KPowerModeSettingNotifierUid);
    iNotifier.Close();
}

void CBTPowerControl::RunL()
{
    switch(iState)
    {
        case EAskingPower:
        {
            iObserver.PowerState(iReply());
            iNotifier.Close();
        }
        break;
        default: break;
    }
}

TInt CBTPowerControl::RunError(TInt aError)
{
    return aError;
}

void CBTPowerControl::TurnBtOn()
{
    TInt err(0);
    err = iNotifier.Connect();
    User::LeaveIfError( err );
    TPckgBuf<TBool> dummy(ETrue);
    iNotifier.StartNotifierAndGetResponse(iStatus, KPowerModeSettingNotifierUid, dummy, iReply);
    iState = EAskingPower;    
    SetActive();
}

TBool CBTPowerControl::IsPowered()
{
    CRepository* rep = CRepository::NewLC( KCRUidBluetoothPowerState );
    
    TInt state;
    rep->Get( KBTPowerState, state );
    CleanupStack::PopAndDestroy(rep);
    
    if(state == EBTPowerOn)
        return ETrue;
    else
        return EFalse;
}
