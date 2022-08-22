TEMPLATE=app
CONFIG+=debug_and_release
CONFIG(debug, debug|release) {
    DESTDIR=$$PWD/dep/bin_debug
    LIBS+=-L$$PWD/dep/lib_debug
    CONFIG += console
}
else{
    DESTDIR=$$PWD/dep/bin
    LIBS+=-L$$PWD/dep/lib
}
