QT              = core gui

contains(QT_MAJOR_VERSION, 5) QT += widgets

TARGET          = world1
TEMPLATE        = lib

DESTDIR         = ../../bin/maps
OBJECTS_DIR     = ../../build/maps/world1/objects
MOC_DIR         = ../../build/maps/world1/moc
UI_DIR          = ../../build/maps/world1/ui
RCC_DIR         = ../../build/maps/world1/rcc
LIBS            = -L../../bin/ -lmdcore
INCLUDEPATH     = . ../../libs
QMAKE_RPATHDIR  = ../../bin/

HEADERS         =         \
    items/all.hpp         \
    items/background.hpp  \
    items/baseground.hpp  \
    items/decor.hpp       \
    items/death_items.hpp \
    items/door.hpp        \
    items/foreground.hpp  \
    items/signs.hpp       \
    stage/level1.hpp      \
    stage/level2.hpp      \
    stage/level3.hpp      \
    stage/level4.hpp      \
    stage/level5.hpp      \
    world1.hpp            \

SOURCES         =         \
    items/background.cpp  \
    items/baseground.cpp  \
    items/decor.cpp       \
    items/death_items.cpp \
    items/door.cpp        \
    items/foreground.cpp  \
    items/signs.cpp       \
    stage/level1.cpp      \
    stage/level2.cpp      \
    stage/level3.cpp      \
    stage/level4.cpp      \
    stage/level5.cpp      \
    world1.cpp            \

RESOURCES       =         \
    img/world1.qrc        \
