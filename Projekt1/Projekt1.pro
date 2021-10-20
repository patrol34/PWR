QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    eurusd.cpp \
    gbpaud.cpp \
    main.cpp \
    projekt.cpp \
    projekt2.cpp \
    usdchf.cpp

HEADERS += \
    eurusd.h \
    gbpaud.h \
    projekt.h \
    projekt2.h \
    usdchf.h

FORMS += \
    eurusd.ui \
    gbpaud.ui \
    projekt.ui \
    projekt2.ui \
    usdchf.ui

TRANSLATIONS += \
    Projekt1_pl_PL.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    zasoby.qrc
