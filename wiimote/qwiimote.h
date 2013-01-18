#ifndef QWIIMOTE_H
#define QWIIMOTE_H

// http://wiibrew.org/wiki/Wiimote
// http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Wii_Motion_Plus
// http://druid.caughq.org/presentations/turbo/Wiimote-Hacking.pdf

#include <QObject>
#include <QAccelerometerReading>
#include <QtDeclarative>

QTM_USE_NAMESPACE

class QWiimotePrivate;

class QWiimoteAccelerometerData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int x READ x)
    Q_PROPERTY(int y READ y)
    Q_PROPERTY(int z READ z)

    Q_CLASSINFO("Author", "Sebastiano Galazzo")
    Q_CLASSINFO("Email", "sebastiano.galazzo@gmail.com")

public:
    QWiimoteAccelerometerData(QObject* parent=0);
    QWiimoteAccelerometerData(const QWiimoteAccelerometerData&);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    int z() const;
    void setZ(int z);

private:
    int _x;
    int _y;
    int _z;

friend class QWiimote;
};

class QWiimoteMotionPlusData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal yaw READ yaw)
    Q_PROPERTY(qreal roll READ roll)
    Q_PROPERTY(qreal pitch READ pitch)
    Q_PROPERTY(bool yawSlowMode READ yawSlowMode)
    Q_PROPERTY(bool rollSlowMode READ rollSlowMode)
    Q_PROPERTY(bool pitchSlowMode READ pitchSlowMode)
    Q_PROPERTY(bool extentionConnected READ extentionConnected)

    Q_PROPERTY(qreal magnitude READ magnitude)

    Q_CLASSINFO("Author", "Sebastiano Galazzo")
    Q_CLASSINFO("Email", "sebastiano.galazzo@gmail.com")

public:
    QWiimoteMotionPlusData(QObject* parent=0);
    QWiimoteMotionPlusData(const QWiimoteMotionPlusData&);

    qreal yaw() const;
    void setYaw(qreal yaw);

    qreal roll() const;
    void setRoll(qreal roll);

    qreal pitch() const;
    void setPitch(qreal pitch);

    bool yawSlowMode() const;
    void setYawSlowMode(bool value);

    bool rollSlowMode() const;
    void setRollYawSlowMode(bool value);

    bool pitchSlowMode() const;
    void setPitchYawSlowMode(bool value);

    bool extentionConnected() const;
    void setExtentionConnected(bool value);

    qreal magnitude() const;
    void setMagnitude(qreal magnitude);

private:
    int _yaw;
    int _roll;
    int _pitch;
    int _magnitude;

    bool _yawSlowMode;
    bool _rollSlowMode;
    bool _pitchSlowMode;

    bool _extentionConnected;

friend class QWiimote;
};

QML_DECLARE_TYPE(QWiimoteAccelerometerData)
QML_DECLARE_TYPE(QWiimoteMotionPlusData)

class QWiimote : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWiimote)
    Q_ENUMS(WiimoteStatus)
    Q_ENUMS(DataType)
    Q_ENUMS(WiimoteButton)
    Q_ENUMS(MotionPlusState)
    Q_ENUMS(WiimoteLed)
    Q_PROPERTY(int battery READ batteryLevel)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth)
    Q_PROPERTY(QWiimoteAccelerometerData* accelerometer READ accelerometer)
    Q_PROPERTY(QWiimoteMotionPlusData* gyroscope READ gyroscope)
    Q_CLASSINFO("Author", "Sebastiano Galazzo")
    Q_CLASSINFO("Email", "sebastiano.galazzo@gmail.com")

public:
    QWiimote(QObject* parent=0);
    ~QWiimote();

    static const int MaxReportSize;
    static const int smoothingAccelerometerThreshold; ///< Raw acceleration threshold for non-smoothed data.
    static const int smoothingGyroscopeThreshold; ///< Raw gyroscope threshold for non-smoothed data.
    static const int smoothingMagnitudeThreshold; ///< Raw magnitude threshold for non-smoothed data.

    static const quint16 MOTIONPLUS_TIME;          ///< Time required to calibrate the MotionPlus.
    static const qreal   DEGREES_PER_SECOND_SLOW;  ///< MotionPlus speed (slow).
    static const qreal   DEGREES_PER_SECOND_FAST;  ///< MotionPlus speed (fast).

    enum WiimoteReport {
        Input  = 0xa1,
        Output = 0xa2,
        Zero = 0x00,
        Continuous = 0x0,
        Continuous2 = 0x4,
        WriteMemory = 0x16,
        ReadMemory = 0x17,
        Error = 0x22
    };

    enum WiimoteID {
        Led  = 0x11,
        DataReporting  = 0x12,
        CoreButtons  = 0x30,
        CoreButtonsAccelerometer  = 0x31,
        CoreButtons8ExtensionBytes  = 0x32,
        CoreButtonsAccelerometer12IRBytes = 0x33,
        CoreButtons19ExtensionBytes = 0x34,
        CoreButtonsAccelerometer16ExtensionBytes  = 0x35,
        CoreButtons10IRBytes9ExtensionBytes  = 0x36,
        CoreButtonsAccelerometer10IRBytes6ExtensionBytes  = 0x37,
        ExtensionBytes21 = 0x3d
    };

    enum WiimoteStatus {
        Status = 0x15
    };

    /** Flags to check if one of the Wiimote buttons has been pressed. */
    enum WiimoteButton {
            ButtonLeft  = 0x0100,
            ButtonRight = 0x0200,
            ButtonDown  = 0x0400,
            ButtonUp    = 0x0800,
            ButtonPlus  = 0x1000,
            ButtonHome  = 0x0080,
            ButtonMinus = 0x0010,
            ButtonTwo   = 0x0001,
            ButtonOne   = 0x0002,
            ButtonB     = 0x0004,
            ButtonA     = 0x0008
        };

    /** State of the MotionPlus extension. */
    enum MotionPlusState {
        MotionPlusInactive,   ///< Initial state.
        MotionPlusActivated,  ///< The MotionPlus has been activated by the user, but not by hardware.
        MotionPlusWorking,    ///< The MotionPlus is working but it is not calibrated.
        MotionPlusCalibrated  ///< The MotionPlus is calibrated and its data is now used.
    };

    /** Flags to check if one of the Wiimote buttons has been pressed. */
    enum WiimoteLed {
        Rumble = 0x01,
        Led1   = 0x10,
        Led2   = 0x20,
        Led3   = 0x40,
        Led4   = 0x80
    };


    Q_INVOKABLE void setLed(WiimoteLed led);
    Q_INVOKABLE void enableCoreButtons();
    Q_INVOKABLE void enableCoreButtonsAndAccelerometer();
    Q_INVOKABLE void enableCoreButtonsAccelerometerExtention();
    Q_INVOKABLE void enableMotionPlus();
    Q_INVOKABLE void disableMotionPlus();
    Q_INVOKABLE void requestCalibrationData();
    int batteryLevel(){ return this->battery;}
    QWiimoteAccelerometerData* accelerometer() const;
    QWiimoteMotionPlusData* gyroscope() const;

    bool smooth();
    void setSmooth(bool value);

public slots:
    void start();

private slots:
    void receive(QByteArray&);

signals:
    void connected();
    void disconnected();
    void deviceSelected(QString address);
    void powerOn(bool error);
    void sendCompleted();
    void extentionControllerPlugged();
    void accelerometerChanged();
    void motionPlusChanged();
    void buttonPressed(int button);
    void buttonLeft();
    void buttonRight();
    void buttonDown();
    void buttonUp();
    void buttonPlus();
    void buttonTwo();
    void buttonOne();
    void buttonB();
    void buttonA();
    void buttonMinus();
    void buttonHome();
    void error(int error);

private:
    void getStatus();
    void manageCoreButtons(QByteArray&);
    void manageAccelerometer(QByteArray&);
    void manageGyroscope(QByteArray&);
    void manageStatus(QByteArray&);
    void manageError(QByteArray&);

private:
    int battery;
    bool _batteryIsNearlyEmpty;
    bool _extentionControllerPlugged;
    bool _speakerEnabled;
    bool _smooth;

private:
    QWiimotePrivate *d;  //pointer to implementation

    QWiimoteAccelerometerData* _accelerometer;
    QWiimoteMotionPlusData* _gyroscope;


};

#endif // QWIIMOTE_H
