QT              = core gui

contains(QT_MAJOR_VERSION, 5) QT += widgets

TARGET          = world2
TEMPLATE        = lib

DESTDIR         = ../../bin/maps
OBJECTS_DIR     = ../../build/maps/world2/objects
MOC_DIR         = ../../build/maps/world2/moc
UI_DIR          = ../../build/maps/world2/ui
RCC_DIR         = ../../build/maps/world2/rcc
LIBS            = -L../../bin/ -lmdcore
INCLUDEPATH     = . ../../libs
QMAKE_RPATHDIR  = ../../bin/

HEADERS         =         \
    world2.hpp            \

SOURCES         =         \
    world2.cpp            \

RESOURCES       =         \
    img/world2.qrc        \
