#include "qwiimote.h"
#include "qwiimoteprivate.h"
#include <QDebug>

const int QWiimote::MaxReportSize = 22;
const int QWiimote::smoothingAccelerometerThreshold = 3;
const int QWiimote::smoothingGyroscopeThreshold = 2;
const int QWiimote::smoothingMagnitudeThreshold = 0;

const quint16 QWiimote::MOTIONPLUS_TIME = 8000;
const qreal   QWiimote::DEGREES_PER_SECOND_SLOW = 8192.0 / 595.0;
const qreal   QWiimote::DEGREES_PER_SECOND_FAST = (QWiimote::DEGREES_PER_SECOND_SLOW * 440) / 2000;


QWiimote::QWiimote(QObject* parent) :
    QObject(parent)
    ,battery(0)
    ,_accelerometer( new QWiimoteAccelerometerData())
    ,_gyroscope( new QWiimoteMotionPlusData())
{
    QT_TRAP_THROWING(d = QWiimotePrivate::NewL(*this));
}

QWiimote::~QWiimote(){
    delete d;
}

bool QWiimote::smooth(){
    return this->_smooth;
}

void QWiimote::setSmooth(bool value){
    this->_smooth = value;
}

void QWiimote::start() {
    d->Connect();
}

void QWiimote::setLed(WiimoteLed led) {
    QByteArray data;
    data.append(QWiimote::Output);
    data.append(QWiimote::Led);

    switch(led) {
    case QWiimote::Led1 : data.append(QWiimote::Led1); break;
    case QWiimote::Led2 : data.append(QWiimote::Led2); break;
    case QWiimote::Led3 : data.append(QWiimote::Led3); break;
    case QWiimote::Led4 : data.append(QWiimote::Led4); break;
    default : break;
    }
    qDebug() << "Sending data:" << data.toHex();

    d->SendData(data);
}

void QWiimote::enableCoreButtons() {
    QByteArray data;
    data.append(QWiimote::Output);
    data.append(QWiimote::DataReporting);    
    data.append(QWiimote::Continuous);
    data.append(QWiimote::CoreButtons);
    qDebug() << "Sending data:" << data.toHex();

    d->SendData(data);
}

void QWiimote::enableCoreButtonsAndAccelerometer() {
    QByteArray data;
    data.append(QWiimote::Output);
    data.append(QWiimote::DataReporting);
    data.append(QWiimote::Continuous2);
    data.append(QWiimote::CoreButtonsAccelerometer);
    qDebug() << "Sending data:" << data.toHex();
    d->SendData(data);
}

void QWiimote::enableCoreButtonsAccelerometerExtention(){
    QByteArray data;
    data.append(QWiimote::Output);
    data.append(QWiimote::DataReporting);
    data.append(QWiimote::Continuous2);
    data.append(QWiimote::CoreButtonsAccelerometer16ExtensionBytes);
    qDebug() << "Sending data:" << data.toHex();
    d->SendData(data);
}

void QWiimote::getStatus() {
    QByteArray data;
    data.append(QWiimote::Output);
    data.append(QWiimote::Status);
    data.append(QWiimote::Zero);
    qDebug() << "Sending data:" << data.toHex();
    d->SendData(data);
}

/**
 * Request the calibration data from the Wiimote.
 * @return True if the report was sent correctly.
 */
void QWiimote::requestCalibrationData()
{
    QByteArray data;
    data.append(QWiimote::Output);
    data.append(QWiimote::ReadMemory); // Report type.
    data.append((char)(0x00 | (QWiimote::Led1 & QWiimote::Rumble))); // Read from the EEPROM.
    data.append((char)0x16); // Memory position.
    data.append((char)0x00);
    data.append((char)0x00);
    data.append((char)0x00); // Data size.
    data.append((char)0x20);
    qDebug() << "Sending data:" << data.toHex();
    d->SendData(data);
}


/**
 * Enable the MotionPlus extension.
 */
void QWiimote::enableMotionPlus()
{
    QByteArray data;
    data.append(QWiimote::Output);
    data.append(QWiimote::WriteMemory); // Report type.

    data.append((char)0x4);// | (QWiimote::Led1 & QWiimote::Rumble))); // Write to the registers.

    data.append((char)0xA6); // Memory position.
    data.append((char)0x00);
    data.append((char)0xFE);

    data.append((char)0x01); // Data size.
    data.append((char)0x04); // Activate the MotionPlus.*/
    for( register int i = 0 ; i < 15; i++) data.append(QWiimote::Zero);

    qDebug() << "Sending data:" << data.toHex();
    // Write 0x04 to register 0xA600FE.
    d->SendData(data);
}

/**
 * Disable the MotionPlus extension.
 */
void QWiimote::disableMotionPlus()
{
    QByteArray data;
    data.append(QWiimote::Output);

    data.append((char)0x4);// | (QWiimote::Led1 & QWiimote::Rumble))); // Write to the registers.

    data.append((char)0xA4); // Memory position.
    data.append((char)0x00);
    data.append((char)0xF0);
    data.append((char)0x01); // Data size.
    data.append((char)0x55); // Disable the MotionPlus.*/
    for( register int i = 0 ; i < 15; i++) data.append(QWiimote::Zero);

    qDebug() << "Sending data:" << data.toHex();
    // Write 0x55 to register 0xA400F0
    d->SendData(data);
}

void QWiimote::receive(QByteArray& data)  {
    if( data.size() < 2 ){
        //qDebug() << "QWiimote::receive: buffer size "<< QString::number(data.size());
        return;
    }

    if( data[0] != QWiimote::Input ) {
        qDebug() << "QWiimote::receive: is not input report " << data[0];
        return;
    }
    qDebug() << "Received:" << data.toHex();

    switch((int) data[1]) {
    case 0x20 : manageStatus(data); break;
    case QWiimote::Error : manageError(data); break;
    case QWiimote::CoreButtons :{
        manageCoreButtons(data);        
    } break;
    case QWiimote::CoreButtonsAccelerometer:{
        manageCoreButtons(data);
        manageAccelerometer(data);
    } break;
    case QWiimote::CoreButtonsAccelerometer16ExtensionBytes : {
        manageCoreButtons(data);
        manageAccelerometer(data);
        manageGyroscope(data);
    } break;
    default : qDebug() << "Received:" << data.toHex(); break;
    }
}

void QWiimote::manageStatus(QByteArray& data)
{

    /*
    Bit Mask 	Meaning
    0 	0x01 	Battery is nearly empty
    1 	0x02 	An Extension Controller is connected
    2 	0x04 	Speaker enabled
    3 	0x08 	IR camera enabled
    4 	0x10 	LED 1
    5 	0x20 	LED 2
    6 	0x40 	LED 3
    7 	0x80 	LED 4
    */

    _batteryIsNearlyEmpty = data[4] & 1;
    _extentionControllerPlugged = (data[4] & 2) >> 1;
    _speakerEnabled = (data[4] & 4) >> 2;
    battery = data[7];

    if( _extentionControllerPlugged ) emit extentionControllerPlugged();

    qDebug() << "Battery level : " << QString::number(data[7]);
}

void QWiimote::manageError(QByteArray& data) {

    qDebug() << "Error code : " << QString::number(data[6]);

    emit error(data[4]);
}

void QWiimote::manageAccelerometer(QByteArray& data) {

    /*int temp = (data[4] & 0xFF) << 2;
    temp |= (data[2] & 0x30) >> 4;
    if( !_smooth || (_smooth && abs(temp - _accelerometer->_x)> QWiimote::smoothingAccelerometerThreshold ) )
    _accelerometer->_x  =  temp;

    temp = (data[5] & 0xFF) << 2;
    temp |= (data[3] & 0x20) >> 4;
    if( !_smooth || (_smooth && abs(temp - _accelerometer->_y)> QWiimote::smoothingAccelerometerThreshold ) )
    _accelerometer->_y  = temp;

    temp = (data[6] & 0xFF) << 2;
    temp  |= (data[3] & 0x40) >> 5;
    if( !_smooth || (_smooth && abs(temp - _accelerometer->_z)> QWiimote::smoothingAccelerometerThreshold ) )
    _accelerometer->_z  =  temp;*/


    int temp = (data[4] & 0xFF) << 2;
    temp |= (data[2] & 0x60) >> 5;
    if( !_smooth || (_smooth && abs(temp - _accelerometer->_x)> QWiimote::smoothingAccelerometerThreshold ) )
    _accelerometer->_x  =  temp;

    temp = (data[5] & 0xFF) << 2;
    temp |= (data[3] & 0x20) >> 4;
    if( !_smooth || (_smooth && abs(temp - _accelerometer->_y)> QWiimote::smoothingAccelerometerThreshold ) )
    _accelerometer->_y  = temp;

    temp = (data[6] & 0xFF) << 2;
    temp  |= (data[3] & 0x40) >> 5;
    if( !_smooth || (_smooth && abs(temp - _accelerometer->_z)> QWiimote::smoothingAccelerometerThreshold ) )
    _accelerometer->_z  =  temp;

    emit accelerometerChanged();
}

QWiimoteAccelerometerData* QWiimote::accelerometer() const {
    return this->_accelerometer;
}

void QWiimote::manageGyroscope(QByteArray& data) {

    _gyroscope->_yawSlowMode = (data[10] >> 1) & 1;
    _gyroscope->_pitchSlowMode = data[10] & 1;
    _gyroscope->_rollSlowMode = (data[11] >> 1) & 1;
    _gyroscope->_extentionConnected = data[11] & 1;

    float temp  = (data[7]  & 0xFF) | ((data[10] >> 2) << 8);
          temp /= ( _gyroscope->_yawSlowMode ? QWiimote::DEGREES_PER_SECOND_SLOW : QWiimote::DEGREES_PER_SECOND_FAST );
    if( !_smooth || (_smooth &&abs(temp - _gyroscope->_yaw)> QWiimote::smoothingGyroscopeThreshold ) ) {
        _gyroscope->_yaw  = temp;
    }
    temp  = (data[8]  & 0xFF)| ((data[11]  >> 2) << 8);
    temp /= ( _gyroscope->_rollSlowMode ? QWiimote::DEGREES_PER_SECOND_SLOW : QWiimote::DEGREES_PER_SECOND_FAST );
    if( !_smooth || (_smooth &&abs(temp - _gyroscope->_roll)> QWiimote::smoothingGyroscopeThreshold ) ) {
        _gyroscope->_roll  = temp;
    }
    temp  = (data[9]  & 0xFF) | ((data[12] >> 2) << 8);
    temp /= ( _gyroscope->_pitchSlowMode ? QWiimote::DEGREES_PER_SECOND_SLOW : QWiimote::DEGREES_PER_SECOND_FAST );
    if( !_smooth || (_smooth && abs(temp - _gyroscope->_pitch)> QWiimote::smoothingGyroscopeThreshold ) ) {
        _gyroscope->_pitch  = temp;
    }

    temp = sqrt( (pow((double)_gyroscope->_yaw,2) + pow((double)_gyroscope->_roll,2) + pow((double)_gyroscope->_pitch,2)) );
    if( !_smooth || (_smooth && abs(temp - _gyroscope->_magnitude)> QWiimote::smoothingMagnitudeThreshold ) )
    _gyroscope->_magnitude  =  temp;

    emit motionPlusChanged();
}

QWiimoteMotionPlusData* QWiimote::gyroscope() const {
    return this->_gyroscope;
}

void QWiimote::manageCoreButtons(QByteArray& data) {

   // int command = (data[0]<<8) | data[1] ;

    int command = (data[2]<<8) | data[3] ;
    /*qDebug() << "QWiimote::manageCoreButtons (RAW):" << data.toHex();
    qDebug() << "QWiimote::manageCoreButtons (HEX):" << data.mid(2,2).toHex();
    qDebug() << "QWiimote::manageCoreButtons (INT):" << command;
    qDebug() << "QWiimote::manageCoreButtons (ButtonDown):" << ButtonDown;
    qDebug() << "QWiimote::manageCoreButtons (ButtonHome):" << ButtonHome;
    qDebug() << "QWiimote::manageCoreButtons (ButtonMinus):" <<ButtonMinus;*/

    switch(command){
    case QWiimote::ButtonLeft  :  { emit buttonLeft();  emit buttonPressed(QWiimote::ButtonLeft);  break;}
    case QWiimote::ButtonRight :  { emit buttonRight(); emit buttonPressed(QWiimote::ButtonRight); break;}
    case QWiimote::ButtonDown  :  { emit buttonDown();  emit buttonPressed(QWiimote::ButtonDown);  break;}
    case QWiimote::ButtonUp    :  { emit buttonUp();    emit buttonPressed(QWiimote::ButtonUp);    break;}
    case QWiimote::ButtonPlus  :  { emit buttonPlus();  emit buttonPressed(QWiimote::ButtonPlus);  break;}
    case QWiimote::ButtonTwo   :  { emit buttonTwo();   emit buttonPressed(QWiimote::ButtonTwo);   break;}
    case QWiimote::ButtonOne   :  { emit buttonOne();   emit buttonPressed(QWiimote::ButtonOne);   break;}
    case QWiimote::ButtonA     :  { emit buttonA();     emit buttonPressed(QWiimote::ButtonA);     break;}
    case QWiimote::ButtonB     :  { emit buttonB();     emit buttonPressed(QWiimote::ButtonB);     break;}
    case QWiimote::ButtonMinus :  { emit buttonMinus(); emit buttonPressed(QWiimote::ButtonMinus); break;}
    case QWiimote::ButtonHome  :  { emit buttonHome();  emit buttonPressed(QWiimote::ButtonHome);  break;}
    default : emit buttonPressed(command); break;
    }
}

QWiimoteAccelerometerData::QWiimoteAccelerometerData(QObject* parent) :
    QObject(parent)
  ,_x(0)
  ,_y(0)
  ,_z(0)
{

}

QWiimoteAccelerometerData::QWiimoteAccelerometerData(const QWiimoteAccelerometerData& data){
    this->_x = data._x;
    this->_y = data._y;
    this->_z = data._z;
}

int QWiimoteAccelerometerData::x() const{
    return this->_x;
}

void QWiimoteAccelerometerData::setX(int x){
    this->_x = x;
}

int QWiimoteAccelerometerData::y() const{
    return this->_y;
}

void QWiimoteAccelerometerData::setY(int y){
    this->_y = y;
}

int QWiimoteAccelerometerData::z() const{
    return this->_z;
}

void QWiimoteAccelerometerData::setZ(int z){
    this->_z = z;
}

// MotionPlus
QWiimoteMotionPlusData::QWiimoteMotionPlusData(QObject* parent) :
    QObject(parent)
  ,_yaw(0)
  ,_roll(0)
  ,_pitch(0)
  ,_yawSlowMode(false)
  ,_rollSlowMode(false)
  ,_pitchSlowMode(false)
  ,_extentionConnected(false)
  ,_magnitude(0)
{

}

QWiimoteMotionPlusData::QWiimoteMotionPlusData(const QWiimoteMotionPlusData& data){
    this->_yaw = data._yaw;
    this->_roll = data._roll;
    this->_pitch = data._pitch;
    this->_pitch = data._magnitude;
    this->_yawSlowMode = data._yawSlowMode;
    this->_rollSlowMode = data._rollSlowMode;
    this->_pitchSlowMode = data._pitchSlowMode;
    this->_extentionConnected = data._extentionConnected;
}

qreal QWiimoteMotionPlusData::yaw() const{
    return this->_yaw;
}

void QWiimoteMotionPlusData::setYaw(qreal yaw){
    this->_yaw = yaw;
}

qreal QWiimoteMotionPlusData::roll() const{
    return this->_roll;
}

void QWiimoteMotionPlusData::setRoll(qreal roll){
    this->_roll = roll;
}

qreal QWiimoteMotionPlusData::pitch() const{
    return this->_pitch;
}

void QWiimoteMotionPlusData::setPitch(qreal pitch){
    this->_pitch = pitch;
}

qreal QWiimoteMotionPlusData::magnitude() const{
    return this->_magnitude;
}

bool QWiimoteMotionPlusData::yawSlowMode() const{
    return _yawSlowMode;
}

void QWiimoteMotionPlusData::setYawSlowMode(bool value){
    this->_yawSlowMode = value;
}

bool QWiimoteMotionPlusData::rollSlowMode() const{
    return _rollSlowMode;
}

void QWiimoteMotionPlusData::setRollYawSlowMode(bool value){
    this->_rollSlowMode = value;
}

bool QWiimoteMotionPlusData::pitchSlowMode() const{
    return _pitchSlowMode;
}

void QWiimoteMotionPlusData::setPitchYawSlowMode(bool value){
    this->_pitchSlowMode = value;
}

bool QWiimoteMotionPlusData::extentionConnected() const{
    return _extentionConnected;
}

void QWiimoteMotionPlusData::setExtentionConnected(bool value){
    this->_extentionConnected = value;
}

void QWiimoteMotionPlusData::setMagnitude(qreal magnitude){
    this->_magnitude = magnitude;
}
