#include "qwiimoteprivate.h"
#include <QDebug>

QWiimotePrivate::QWiimotePrivate(QWiimote &aPublicAPI) :
    iPublicAPI(aPublicAPI)

{

}

QWiimotePrivate* QWiimotePrivate::NewL(QWiimote &aPublicAPI)
{
    QWiimotePrivate* self = new QWiimotePrivate(aPublicAPI);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
}

QWiimotePrivate::~QWiimotePrivate()
{

}

/**
 * @brief Completes the second phase of Symbian object construction.
 * Put initialization code that could leave here.
 */
void QWiimotePrivate::ConstructL()
{
    iAdvertiser = CBTAdvertiser::NewL();

    iSocketHandler = CSocketHandler::NewL(*this);
    iDeviceFinder = CDeviceFinder::NewL(*this);
    iPowerControl = CBTPowerControl::NewL(*this);
    iPowerControl->TurnBtOn();    
}

void QWiimotePrivate::Disconnect()
{
    iSocketHandler->DisconnectHost();
}

void QWiimotePrivate::Connect()
{
    if(iPowerControl->IsPowered())
    {
        iDeviceFinder->StartDiscoverL();
    } else {
        iPowerControl->TurnBtOn();
    }
}

void QWiimotePrivate::Connected()
{    
    emit iPublicAPI.connected();
   // iPublicAPI.getStatus();
   // iPublicAPI.enableMotionPlus();
}

void QWiimotePrivate::Disconnected()
{   
    emit iPublicAPI.disconnected();
}

void QWiimotePrivate::DeviceSelected(TBTDevAddr aAddr)
{
    TBuf<128> address;
    aAddr.GetReadable(address);
    address.Trim();
    emit iPublicAPI.deviceSelected(QString::fromUtf16(address.Ptr(), address.Length()));

    iSocketHandler->ConnectHost(aAddr);
}


void QWiimotePrivate::PowerState(TBool aOn)
{
    //qDebug() << "QWiimotePrivate::PowerState:" << QString::number(aOn) ;
    if(aOn) {
        iSocketHandler->StartListeningL();
    } else {
        iSocketHandler->DisconnectHost();
        //iAccelerometer->Stop();
        //iBlueMouseContainerView->EnableTouch(EFalse);
    }

    emit iPublicAPI.powerOn(!aOn);
}

void QWiimotePrivate::SendData(QByteArray& buffer)
{
    if( buffer.size() <= 0 ) {
        qDebug() << "QWiimotePrivate::SendData: Incorrect buffer size";
        return;
    }

    int size = buffer.size();

    TUint8* data = (TUint8*)User::AllocLC(size);

    TPtr8 ptr(data,size,size);

    for( int i = 0 ; i < size ; i++ ){
        ptr[i] = buffer[i];
    }

    iSocketHandler->SendDataL(ptr);
    CleanupStack::PopAndDestroy(data);
}

void QWiimotePrivate::Sending() {
    emit iPublicAPI.sendCompleted();
}

void QWiimotePrivate::Receiving(QByteArray buffer) {
    //emit iPublicAPI.receiveCompleted(buffer.toHex());
    iPublicAPI.receive(buffer);
}
