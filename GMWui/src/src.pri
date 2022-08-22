SOURCES	+= \
    $$PWD/main.cpp

HEADERS += \
    $$PWD/globaldefine.h

include ($$PWD/3rdparty/3rdparty.pri)
include ($$PWD/api/api.pri)
include ($$PWD/form/form.pri)

INCLUDEPATH	+= $$PWD/3rdparty 
INCLUDEPATH	+= $$PWD/api 
INCLUDEPATH	+= $$PWD/form

