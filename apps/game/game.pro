#################################################################
#                                                               #
#  Game project                                                 #
#                                                               #
#################################################################

QT              = core gui

contains(QT_MAJOR_VERSION, 5) QT += widgets

TARGET          = MaskedDuck
TEMPLATE        = app

DESTDIR         = ../../bin
OBJECTS_DIR     = ../../build/apps/game/objects
MOC_DIR         = ../../build/apps/game/moc
UI_DIR          = ../../build/apps/game/ui
RCC_DIR         = ../../build/apps/game/rcc
LIBS            = -L../../bin/ -lmdcore -lmdgengine
INCLUDEPATH     = . ../ ../../libs
QMAKE_RPATHDIR  = ../../bin/

SOURCES         =           \
    data/level.cpp          \
    data/player.cpp         \
    data/world.cpp          \
    items/duck.cpp          \
    items/info_item.cpp     \
    items/lose_item.cpp     \
    items/menu_item.cpp     \
    items/road.cpp          \
    items/status_game.cpp   \
    items/status_level.cpp  \
    items/status_world.cpp  \
    items/win_item.cpp      \
    items/world_item.cpp    \
    scene/game_over.cpp     \
    scene/scene_level.cpp   \
    scene/scene_menu.cpp    \
    scene/scene_start.cpp   \
    scene/scene_world.cpp   \
    scene/select_world.cpp  \
    main.cpp                \
    mainwindow.cpp          \

HEADERS         =           \
    data/level.hpp          \
    data/player.hpp         \
    data/world.hpp          \
    items/duck.hpp          \
    items/info_item.hpp     \
    items/lose_item.hpp     \
    items/menu_item.hpp     \
    items/road.hpp          \
    items/status_game.hpp   \
    items/status_level.hpp  \
    items/status_world.hpp  \
    items/win_item.hpp      \
    items/world_item.hpp    \
    scene/game_over.hpp     \
    scene/scene_level.hpp   \
    scene/scene_menu.hpp    \
    scene/scene_start.hpp   \
    scene/scene_world.hpp   \
    scene/select_world.hpp  \
    constant.hpp            \
    mainwindow.hpp          \

RESOURCES       =           \
    img/game.qrc            \
