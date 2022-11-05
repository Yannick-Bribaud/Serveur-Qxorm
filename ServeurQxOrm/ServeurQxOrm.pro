QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/OnlineCntroller.cpp \
    UserOnline.cpp \
    data.cpp \
    main.cpp \
    ServerUi.cpp \
    property.cpp \
    server.cpp

HEADERS += \
    Controller/OnlineCntroller.h \
    ServerUi.h \
    UserOnline.h \
    data.h \
    property.h \
    server.h

FORMS += \
    UserOnline.ui \
    serverui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES += \
    res.qrc


RC_ICONS = Server_Icone.ico
