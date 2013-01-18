/*
 ============================================================================
 Name		: BTAdvertiser.cpp
 Author	  : Juhana Paavola
 Version	 : 1.0
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
 Free to use, use freely.
 Description : CBTAdvertiser implementation
 ============================================================================
 */

#include "BTAdvertiser.h"
#include "common.h"

CBTAdvertiser::CBTAdvertiser()
{
}

CBTAdvertiser::~CBTAdvertiser()
{
    TRAPD(err,StopL());
}

CBTAdvertiser* CBTAdvertiser::NewLC()
{
    CBTAdvertiser* self = new (ELeave) CBTAdvertiser();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

CBTAdvertiser* CBTAdvertiser::NewL()
{
    CBTAdvertiser* self = CBTAdvertiser::NewLC();
    CleanupStack::Pop();
    return self;
}

void CBTAdvertiser::ConstructL()
{
	StartL();
}

void CBTAdvertiser::StartL()
{
    User::LeaveIfError(iSdp.Connect());    
    User::LeaveIfError(iSdpDB.Open(iSdp));
   
    BuildHIDL();
    
    UpdateAvailabilityL(ETrue);    
}

void CBTAdvertiser::StopL()
{
    UpdateAvailabilityL(EFalse);
    if(iRecordHandle != 0)
        {
        iSdpDB.DeleteRecordL(iRecordHandle);
        iRecordHandle = 0;
        }        
    iSdpDB.Close();
    iSdp.Close();
}

void CBTAdvertiser::UpdateAvailabilityL(TBool aAvailable)
{
    TInt state = aAvailable ? 0xFF : 0x00;
    iSdpDB.UpdateAttributeL(iRecordHandle,KSdpAttrIdServiceAvailability,state);
    iSdpDB.UpdateAttributeL(iRecordHandle,KSdpAttrIdServiceRecordState,++iRecordState);
}

void CBTAdvertiser::BuildHIDL()
{
    iSdpDB.CreateServiceRecordL(TUUID(TUint16(KHidService)),iRecordHandle);

    CSdpAttrValueDES* protocolDescList = CSdpAttrValueDES::NewDESL(NULL);
    CSdpAttrValueDES* addProtocolDescList = CSdpAttrValueDES::NewDESL(NULL);
    CSdpAttrValueDES* profileDescList = CSdpAttrValueDES::NewDESL(NULL);    
    CSdpAttrValueDES* browseGroupList = CSdpAttrValueDES::NewDESL(NULL);
    CSdpAttrValueDES* langList = CSdpAttrValueDES::NewDESL(NULL);
    CSdpAttrValueBoolean* reconnect = CSdpAttrValueBoolean::NewBoolL(ETrue);
    CSdpAttrValueBoolean* virtualCable = CSdpAttrValueBoolean::NewBoolL(ETrue);
    CSdpAttrValueBoolean* sdpDisp = CSdpAttrValueBoolean::NewBoolL(EFalse);
    
    CSdpAttrValueBoolean* battery = CSdpAttrValueBoolean::NewBoolL(ETrue);
    CSdpAttrValueBoolean* remoteWake = CSdpAttrValueBoolean::NewBoolL(ETrue);
    CSdpAttrValueDES* hidDescList = CSdpAttrValueDES::NewDESL(NULL);

    CSdpAttrValueUint* parserVersion = CSdpAttrValueUint::NewUintL(TSdpIntBuf<TUint16>(0x0111));
    CSdpAttrValueUint* releaseNumber = CSdpAttrValueUint::NewUintL(TSdpIntBuf<TUint16>(0x0100));
    CSdpAttrValueUint* countryCode = CSdpAttrValueUint::NewUintL(TSdpIntBuf<TUint8>(0x21));
    CSdpAttrValueUint* subClass = CSdpAttrValueUint::NewUintL(TSdpIntBuf<TUint8>(KMouseSubClassID)); //mouse
    CSdpAttrValueBoolean* normallyConnectable = CSdpAttrValueBoolean::NewBoolL(ETrue);
    CSdpAttrValueBoolean* bootDevice = CSdpAttrValueBoolean::NewBoolL(ETrue);
    CSdpAttrValueUint* profileVersion = CSdpAttrValueUint::NewUintL(TSdpIntBuf<TUint16>(0x0100));
    
    
    CSdpAttrValueDES* baseLangList = CSdpAttrValueDES::NewDESL(NULL);
    CSdpAttrValueDES* serviceClassIdList = CSdpAttrValueDES::NewDESL(NULL);
    CSdpAttrValueUint* supervisionTimeout = CSdpAttrValueUint::NewUintL(TSdpIntBuf<TUint16>(0x1f40));
    
    CleanupStack::PushL(protocolDescList);
    CleanupStack::PushL(addProtocolDescList);
    CleanupStack::PushL(profileDescList);
    CleanupStack::PushL(browseGroupList);
    CleanupStack::PushL(langList);
    CleanupStack::PushL(reconnect);
    CleanupStack::PushL(virtualCable);
    CleanupStack::PushL(sdpDisp);
    CleanupStack::PushL(bootDevice);
    CleanupStack::PushL(battery);
    CleanupStack::PushL(remoteWake);
    
    CleanupStack::PushL(parserVersion);
    CleanupStack::PushL(releaseNumber);
    CleanupStack::PushL(countryCode);
    
    CleanupStack::PushL(hidDescList);
    CleanupStack::PushL(subClass);
    CleanupStack::PushL(normallyConnectable);
    CleanupStack::PushL(profileVersion);
    CleanupStack::PushL(baseLangList);
    CleanupStack::PushL(serviceClassIdList);
    CleanupStack::PushL(supervisionTimeout);

    
    protocolDescList    
        ->StartListL()
            ->BuildDESL()
                ->StartListL()
                    ->BuildUUIDL(TUUID(TUint16(KL2CAP)))
                    ->BuildUintL(TSdpIntBuf<TUint8>(KControlChannel))
                ->EndListL()
            ->BuildDESL()
                ->StartListL()
                    ->BuildUUIDL(TUUID(TUint16(KHIDDesc)))
                ->EndListL()
            ->BuildDESL()
                ->StartListL()
                    ->BuildUUIDL(TUUID(TUint16(KL2CAP)))
                    ->BuildUintL(TSdpIntBuf<TUint8>(KInterruptChannel))
                ->EndListL()
            ->BuildDESL()
                ->StartListL()
                    ->BuildUUIDL(TUUID(TUint16(KHIDDesc)))
                ->EndListL()
        ->EndListL();

    addProtocolDescList
    ->StartListL()
        ->BuildDESL()
            ->StartListL()
                ->BuildUUIDL(TUUID(TUint16(KL2CAP)))
                ->BuildUintL(TSdpIntBuf<TUint8>(KInterruptChannel))
            ->EndListL()
        ->BuildDESL()
            ->StartListL()
                ->BuildUUIDL(TUUID(TUint16(KHIDDesc)))
            ->EndListL()
        ->BuildDESL()
            ->StartListL()
                ->BuildUUIDL(TUUID(TUint16(KL2CAP)))
                ->BuildUintL(TSdpIntBuf<TUint8>(KControlChannel))
            ->EndListL()
        ->BuildDESL()
            ->StartListL()
                ->BuildUUIDL(TUUID(TUint16(KHIDDesc)))
            ->EndListL()
    ->EndListL();

    profileDescList
    ->StartListL()
        ->BuildDESL()
            ->StartListL()
                ->BuildUUIDL(TUUID(TUint16(KHidService)))
                ->BuildUintL(TSdpIntBuf<TUint16>(0x0100))
            ->EndListL()    
    ->EndListL();
    
    langList
            ->StartListL()
                ->BuildUintL(TSdpIntBuf<TUint16>(KLanguageEnglish)) // en
                ->BuildUintL(TSdpIntBuf<TUint16>(0x006a)) // utf8
                ->BuildUintL(TSdpIntBuf<TUint16>(0x0100)) // version
            ->EndListL();
    
    
    HBufC8* data = NULL;
    TPtr8 ptr(0,0);
    TInt dataSize(0);
    TUint8* desc = NULL;;
    dataSize += KMouseDescSize;
    data = HBufC8::NewLC(dataSize);    
    ptr.Set(data->Des());
    
    desc = (TUint8*)KMouseDesc;
    for(TInt i=0;i<KMouseDescSize;i++)
        {
        ptr.Append(TChar(desc[i]));
        }
    

    hidDescList
    ->StartListL()
        ->BuildDESL()
            ->StartListL()
                ->BuildUintL(TSdpIntBuf<TUint8>(0x22))
                ->BuildStringL(ptr)                
            ->EndListL()
     ->EndListL();
    CleanupStack::PopAndDestroy(data);
        
    baseLangList
    ->StartListL()
        ->BuildDESL()
        ->StartListL()
            ->BuildUintL(TSdpIntBuf<TUint16>(0x0409))
            ->BuildUintL(TSdpIntBuf<TUint16>(0x0100))
        ->EndListL()
    ->EndListL();
    
    serviceClassIdList
    ->StartListL()
        ->BuildUUIDL(TUUID(TUint16(KHidService)))
    ->EndListL();
    
    browseGroupList
    ->StartListL()
        ->BuildUUIDL(TUUID(TUint16(KPublicBrowseGroupUUID)))
    ->EndListL();
    
    
    // set protocol list to the record        
    iSdpDB.UpdateAttributeL(iRecordHandle,KSubClass, *subClass);
    iSdpDB.UpdateAttributeL(iRecordHandle,KCountryCode, *countryCode);
    iSdpDB.UpdateAttributeL(iRecordHandle,KReleaseNumber, *releaseNumber);
    iSdpDB.UpdateAttributeL(iRecordHandle,KParserVersion, *parserVersion);
    iSdpDB.UpdateAttributeL(iRecordHandle,KBootDevice,*bootDevice);    
    iSdpDB.UpdateAttributeL(iRecordHandle,KRemoteWake,*remoteWake);    
    iSdpDB.UpdateAttributeL(iRecordHandle,KBatteryPower,*battery);
    iSdpDB.UpdateAttributeL(iRecordHandle,KVirtualCable,*virtualCable);
    iSdpDB.UpdateAttributeL(iRecordHandle,KReconnectInitiate,*reconnect);    
    iSdpDB.UpdateAttributeL(iRecordHandle,KSdpDisposable,*sdpDisp);    
    iSdpDB.UpdateAttributeL(iRecordHandle,KSdpAttrIdBrowseGroupList,*browseGroupList);                 
    iSdpDB.UpdateAttributeL(iRecordHandle,KSdpAttrIdProtocolDescriptorList,*protocolDescList);    
    iSdpDB.UpdateAttributeL(iRecordHandle,KAdditionalProtocol,*addProtocolDescList);    
    iSdpDB.UpdateAttributeL(iRecordHandle,KSdpAttrIdBluetoothProfileDescriptorList,*profileDescList);    
    iSdpDB.UpdateAttributeL(iRecordHandle,KHIDBaseLangList,*baseLangList);
    iSdpDB.UpdateAttributeL(iRecordHandle,KHIDDescList, *hidDescList);    
    iSdpDB.UpdateAttributeL(iRecordHandle,KHIDProfileVersion,*profileVersion);
    iSdpDB.UpdateAttributeL(iRecordHandle,KHIDNormallyConnectable,*normallyConnectable);
    iSdpDB.UpdateAttributeL(iRecordHandle,KSdpAttrIdServiceClassIDList, *serviceClassIdList);
    iSdpDB.UpdateAttributeL(iRecordHandle,KHIDSupervisionTimeout,*supervisionTimeout);
    
    
    CleanupStack::PopAndDestroy(supervisionTimeout);
    CleanupStack::PopAndDestroy(serviceClassIdList);
    CleanupStack::PopAndDestroy(baseLangList);
    CleanupStack::PopAndDestroy(profileVersion);
    CleanupStack::PopAndDestroy(normallyConnectable);
    CleanupStack::PopAndDestroy(subClass);
    CleanupStack::PopAndDestroy(hidDescList);    
    CleanupStack::PopAndDestroy(countryCode);
    CleanupStack::PopAndDestroy(releaseNumber);
    CleanupStack::PopAndDestroy(parserVersion);    
    CleanupStack::PopAndDestroy(remoteWake);
    CleanupStack::PopAndDestroy(battery);
    CleanupStack::PopAndDestroy(bootDevice);
    CleanupStack::PopAndDestroy(sdpDisp);
    CleanupStack::PopAndDestroy(virtualCable);
    CleanupStack::PopAndDestroy(reconnect);
    CleanupStack::PopAndDestroy(langList);
    CleanupStack::PopAndDestroy(browseGroupList);
    CleanupStack::PopAndDestroy(profileDescList);
    CleanupStack::PopAndDestroy(addProtocolDescList);
    CleanupStack::PopAndDestroy(protocolDescList);
    

    // add a name to the record
    iSdpDB.UpdateAttributeL(iRecordHandle,
                              KSdpAttrIdBasePrimaryLanguage +
                                        KSdpAttrIdOffsetServiceName,
                                    KServiceName());
    
    // add a description to the record
    iSdpDB.UpdateAttributeL(iRecordHandle,
                                    KSdpAttrIdBasePrimaryLanguage +
                                        KSdpAttrIdOffsetServiceDescription,
                                        KServiceDesc());
    
    iSdpDB.UpdateAttributeL(iRecordHandle, 
                            KSdpAttrIdOffsetProviderName + KSdpAttrIdBasePrimaryLanguage,
                            KServiceProvider());    
}
