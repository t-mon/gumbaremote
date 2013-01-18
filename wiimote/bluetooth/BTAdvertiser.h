/*
 ============================================================================
 Name		: BTAdvertiser.h
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CBTAdvertiser declaration
 ============================================================================
 */

#ifndef BTADVERTISER_H
#define BTADVERTISER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <es_sock.h>
#include <bt_sock.h>
#include <btsdp.h>
#include <btmanclient.h>


class CBTAdvertiser : public CBase
    {
public:

	~CBTAdvertiser();

    static CBTAdvertiser* NewL();

    static CBTAdvertiser* NewLC();

private:
    
    void StartL();
    
    void StopL();

    CBTAdvertiser();

    void ConstructL();
    
    void UpdateAvailabilityL(TBool aAvailable);
    
    void BuildHIDL();
    
private:
    
    RSdp                    iSdp;
    RSdpDatabase            iSdpDB;
    TBool                   iAvailable;
    TSdpServRecordHandle    iRecordHandle;
    TInt                    iRecordState;
    };

#endif // BTADVERTISER_H
