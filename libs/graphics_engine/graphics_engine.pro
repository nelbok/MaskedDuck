#################################################################
#                                                               #
#  Graphics engine for the apps.                                #
#                                                               #
#################################################################

QT              = core gui

contains(QT_MAJOR_VERSION, 5) QT += widgets

TARGET          = mdgengine
TEMPLATE        = lib

DESTDIR         = ../../bin
OBJECTS_DIR     = ../../build/libs/graphics_engine/objects
MOC_DIR         = ../../build/libs/graphics_engine/moc
UI_DIR          = ../../build/libs/graphics_engine/ui
RCC_DIR         = ../../build/libs/graphics_engine/rcc
LIBS            = -L../../bin/ -lmdcore
INCLUDEPATH     = . ..
QMAKE_RPATHDIR  = ../../bin/

HEADERS         =           \
    constant.hpp            \
    scene/scene_level.hpp   \

SOURCES     =               \
    scene/scene_level.cpp   \
