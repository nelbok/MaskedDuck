QT              = core gui

contains(QT_MAJOR_VERSION, 5) QT += widgets

TARGET          = world0
TEMPLATE        = lib

DESTDIR         = ../../bin/maps
OBJECTS_DIR     = ../../build/maps/world0/objects
MOC_DIR         = ../../build/maps/world0/moc
UI_DIR          = ../../build/maps/world0/ui
RCC_DIR         = ../../build/maps/world0/rcc
LIBS            = -L../../bin/ -lmdcore
INCLUDEPATH     = . ../../libs
QMAKE_RPATHDIR  = ../../bin/

HEADERS         =         \
    items/background.hpp  \
    items/door.hpp        \
    items/ground.hpp      \
    world0.hpp            \

SOURCES         =         \
    items/background.cpp  \
    items/door.cpp        \
    items/ground.cpp      \
    world0.cpp            \

RESOURCES       =         \
    img/world0.qrc        \
