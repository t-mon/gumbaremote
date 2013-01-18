
CONFIG += mobility
MOBILITY += sensors

INCLUDEPATH += "wiimote"
INCLUDEPATH += "wiimote/bluetooth"

DEFINES += QWIIMOTE

DEPENDPATH  += "wiimote"
#DEPENDPATH  += "./wiimote/bluetooth"

HEADERS +=  BTAdvertiser.h \
            SocketAcceptor.h \
            SocketConnect.h \
            SocketHandler.h \
            qwiimote.h \
            qwiimoteprivate.h \
            common.h \
            MSocketHandlerObserver.h \
            MBlueWiimoteObserver.h \
            DeviceFinder.h \
            BTPowerControl.h

SOURCES += bluetooth/BTAdvertiser.cpp \
           bluetooth/SocketAcceptor.cpp \
           bluetooth/SocketConnect.cpp \
           bluetooth/SocketHandler.cpp \
           bluetooth/DeviceFinder.cpp \
           bluetooth/BTPowerControl.cpp \
           qwiimote.cpp \
           qwiimoteprivate.cpp \

LIBS += -lesock
LIBS += -lbtextnotifiers
LIBS += -lbluetooth
LIBS += -lbtdevice
LIBS += -lsdpdatabase
LIBS += -lHtiBtCommServer
LIBS += -lcentralrepository

symbian:TARGET.CAPABILITY +=  WriteDeviceData NetworkServices LocalServices
