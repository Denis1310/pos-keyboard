QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commandwindow.cpp \
    comport.cpp \
    configuration.cpp \
    database.cpp \
    listpresets.cpp \
    main.cpp \
    mainwindow.cpp \
    settingswindow.cpp

HEADERS += \
    commandwindow.h \
    comport.h \
    configuration.h \
    database.h \
    enums.h \
    listpresets.h \
    mainwindow.h \
    settingswindow.h

FORMS += \
    commandwindow.ui \
    mainwindow.ui \
    settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
