#################################################################
#                                                               #
#  Core structure for the apps.                                 #
#                                                               #
#################################################################

QT              = core gui

contains(QT_MAJOR_VERSION, 5) QT += widgets

TARGET          = mdcore
TEMPLATE        = lib

DESTDIR         = ../../bin
OBJECTS_DIR     = ../../build/libs/core/objects
MOC_DIR         = ../../build/libs/core/moc
UI_DIR          = ../../build/libs/core/ui
RCC_DIR         = ../../build/libs/core/rcc
INCLUDEPATH     = . ..

HEADERS         =           \
    items/block.hpp          \
    items/door.hpp          \
    items/egg.hpp           \
    items/life.hpp          \
    stage/boss.hpp          \
    stage/level.hpp         \
    stage/pnj.hpp           \
    map.hpp                 \
    no_copy.hpp             \
    stage.hpp               \
    world.hpp               \
    world_item.hpp          \

SOURCES     =               \
    items/block.cpp          \
    items/door.cpp          \
    items/egg.cpp           \
    items/life.cpp          \
    map.cpp                 \
    world.cpp               \
    world_item.cpp          \

RESOURCES       =           \
    img/core.qrc            \
