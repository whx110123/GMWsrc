TEMPLATE=lib
CONFIG+=dll debug_and_release

CONFIG(debug, debug|release) {
    DESTDIR=$$PWD/dep/lib_debug
    DLLDESTDIR=$$PWD/dep/bin_debug
    LIBS+=-L$$PWD/dep/lib_debug
}
else{
    DESTDIR=$$PWD/dep/lib
    DLLDESTDIR=$$PWD/dep/bin
    LIBS+=-L$$PWD/dep/lib
}



