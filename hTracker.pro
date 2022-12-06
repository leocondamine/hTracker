QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include/
VPATH += src/


SOURCES += \
    checkhabitbtn.cpp \
    main.cpp \
    htracker.cpp \
    newhabit.cpp

HEADERS += \
    include/checkhabitbtn.h \
    include/htracker.h \
    include/newhabit.h

FORMS += \
    ui/checkhabitbtn.ui \
    ui/htracker.ui \
    ui/newhabit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
