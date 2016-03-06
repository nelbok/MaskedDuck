#################################################################
#                                                               #
#  Editor project to help at the creation of the maps.          #
#  Generate all the code for the maps.                          #
#                                                               #
#################################################################

QT              = core gui

contains(QT_MAJOR_VERSION, 5) QT += widgets

TARGET          = MDEditor
TEMPLATE        = app

DESTDIR         = ../../bin
OBJECTS_DIR     = ../../build/apps/editor/objects
MOC_DIR         = ../../build/apps/editor/moc
UI_DIR          = ../../build/apps/editor/ui
RCC_DIR         = ../../build/apps/editor/rcc
LIBS            = -L../../bin/ -lmdcore -lmdgengine
INCLUDEPATH     = . ../ ../../libs
QMAKE_RPATHDIR  = ../../bin/

SOURCES         =                   \
    data/stage/level.cpp            \
    data/generate.cpp               \
    data/resource.cpp               \
    data/world.cpp                  \
    items/road.cpp                  \
    items/world_item.cpp            \
    scene/scene_world.cpp           \
    widget/body/body_level.cpp      \
    widget/body/body_level_view.cpp \
    widget/body/body_world.cpp      \
    widget/body/body_world_view.cpp \
    widget/tools/edit_connexion.cpp \
    widget/tools/edit_resource.cpp  \
    widget/tools/edit_stage.cpp     \
    widget/tools/edit_world.cpp     \
    widget/tools/select_resource.cpp\
    widget/tools/select_world.cpp   \
    widget/body.cpp                 \
    widget/items.cpp                \
    widget/stages.cpp               \
    main.cpp                        \
    mainwindow.cpp                  \
    widget/menu.cpp

HEADERS         =                   \
    data/stage/level.hpp            \
    data/generate.hpp               \
    data/resource.hpp               \
    data/world.hpp                  \
    items/road.hpp                  \
    items/world_item.hpp            \
    scene/scene_world.hpp           \
    widget/body/body_level.hpp      \
    widget/body/body_level_view.hpp \
    widget/body/body_world.hpp      \
    widget/body/body_world_view.hpp \
    widget/tools/edit_connexion.hpp \
    widget/tools/edit_resource.hpp  \
    widget/tools/edit_stage.hpp     \
    widget/tools/edit_world.hpp     \
    widget/tools/select_resource.hpp\
    widget/tools/select_world.hpp   \
    widget/body.hpp                 \
    widget/items.hpp                \
    widget/stages.hpp               \
    mainwindow.hpp                  \
    widget/menu.hpp

RESOURCES +=                        \
    img/editor.qrc                  \
