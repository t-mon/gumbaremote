/*
 ============================================================================
 Name		: BTPowerControl.h
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CBTPowerControl declaration
 ============================================================================
 */

#ifndef BTPOWERCONTROL_H
#define BTPOWERCONTROL_H

#include <e32base.h>
#include <e32std.h>
#include <bttypes.h>
#include <btdevice.h>
#include <centralrepository.h>
#include <btserversdkcrkeys.h>
#include "MBlueWiimoteObserver.h"

const TUid KPowerModeSettingNotifierUid = {0x100059E2};

class CBTPowerControl : public CActive
    {
public:
    ~CBTPowerControl();

    static CBTPowerControl* NewL(MBlueWiimoteObserver& aObserver);

    static CBTPowerControl* NewLC(MBlueWiimoteObserver& aObserver);

    void TurnBtOn();

    TBool IsPowered();
    
private:
    CBTPowerControl(MBlueWiimoteObserver& aObserver);

    void ConstructL();

    void RunL();

    void DoCancel();

    TInt RunError(TInt aError);

private:
    enum TBTPowerControlState
        {
        EAskingPower = 0
        };

    MBlueWiimoteObserver& iObserver;
    TInt            iState;
    TBool           iHasPower;
    RNotifier       iNotifier;
    TPckgBuf<TBool> iReply;
    };

#endif // BTPOWERCONTROL_H
