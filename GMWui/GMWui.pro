include( $$PWD/../bin.pri )
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
}

greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

msvc:QMAKE_CXXFLAGS += /utf-8

TARGET              = GMWui
TEMPLATE            = app
win32:RC_FILE       = rcs/main.rc
CONFIG              += warn_off
DEFINES             += QT_MESSAGELOGCONTEXT

include             ($$PWD/src/src.pri)

INCLUDEPATH         += $$PWD
INCLUDEPATH         += $$PWD/src

RESOURCES += \
	rcs/qrc/font.qrc \
	rcs/qrc/main.qrc \
	rcs/qrc/qm.qrc \
	rcs/qrc/qss.qrc \
	rcs/qrc/res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
	rcs/astyle.astylerc
