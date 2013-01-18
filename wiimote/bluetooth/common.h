/*
========================================================================
 Name        : common.h
 Author      : Juhana Paavola
 Copyright   : Code sample by Juhana Paavola <juhana.paavola@gmail.com>
Free to use, use freely.
 Description : 
========================================================================
*/

#ifndef COMMON_H_
#define COMMON_H_

_LIT(KServiceName,"BlueMouse");
_LIT(KServiceDesc,"Symbian device as HID device");
_LIT(KServiceProvider,"Code example by Juhana Paavola <juhana.paavola@gmail.com>");

const TUid KAppUid = {0xED5B591E};
const TUint16 KHidService = 0x1124;
const TUint16 KHIDDesc = 0x0011;
const TUint16 KAdditionalProtocol = 0x000d;
const TUint16 KReleaseNumber = 0x0200;
const TUint16 KParserVersion = 0x0201;
const TUint16 KSubClass = 0x0202;
const TUint16 KCountryCode = 0x0203;
const TUint16 KVirtualCable = 0x0204;
const TUint16 KReconnectInitiate = 0x0205;
const TUint16 KHIDDescList = 0x0206;
const TUint16 KHIDBaseLangList = 0x0207;
const TUint16 KSdpDisposable = 0x0208;
const TUint16 KBatteryPower = 0x0209;
const TUint16 KRemoteWake = 0x020A;
const TUint16 KHIDProfileVersion = 0x020B;
const TUint16 KHIDSupervisionTimeout=0x020c;
const TUint16 KHIDNormallyConnectable = 0x020D;
const TUint16 KBootDevice = 0x020E;
const TUint8 KInterruptChannel = 0x13;
const TUint8 KControlChannel = 0x11;
const TUint8 KMouseSubClassID = 0x80;
const TInt KDataSize = 55;
const TUint KAccPropertyX = 0x0001;
const TUint KAccPropertyY = 0x0002;
const TUint KAccPropertyZ = 0x0003;


const TInt KReportID = 0x03;
const TInt KMouseDescSize=52;
const TUint8 KMouseDesc[KMouseDescSize] = {
        0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
        0x09, 0x02,                    // USAGE (Mouse)
        0xa1, 0x01,                    // COLLECTION (Application)
        0x85, KReportID,                    //   REPORT_ID (1)
        0x09, 0x01,                    //   USAGE (Pointer)
        0xa1, 0x00,                    //   COLLECTION (Physical)
        0x05, 0x09,                    //     USAGE_PAGE (Button)
        0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
        0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
        0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
        0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
        0x95, 0x03,                    //     REPORT_COUNT (3)
        0x75, 0x01,                    //     REPORT_SIZE (1)
        0x81, 0x02,                    //     INPUT (Data,Var,Abs)
        0x95, 0x01,                    //     REPORT_COUNT (1)
        0x75, 0x05,                    //     REPORT_SIZE (5)
        0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
        0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
        0x09, 0x30,                    //     USAGE (X)
        0x09, 0x31,                    //     USAGE (Y)
        0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
        0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
        0x75, 0x08,                    //     REPORT_SIZE (8)
        0x95, 0x02,                    //     REPORT_COUNT (2)
        0x81, 0x06,                    //     INPUT (Data,Var,Rel)
        0xc0,                          //   END_COLLECTION
        0xc0                           // END_COLLECTION
};

enum TMouseButton {
    ERightDown = 0,
    ERightUp,
    ELeftDown,
    ELeftUp,
    EMiddleDown,
    EMiddleUp
};

class TBlueMouseSettings
    {
public:
    TBlueMouseSettings():              
        iMouseInterval(0),
        iMouseEnable(EFalse),
        iResolution(72)
    {    
    }
    
    TInt    iMouseInterval;
    TBool   iMouseEnable;
    TInt    iResolution;
    };

#endif /* COMMON_H_ */
