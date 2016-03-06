#include <QCoreApplication>
#include <QGraphicsView>

#include "game/scene/game_over.hpp"
#include "game/scene/scene_level.hpp"
#include "game/scene/scene_menu.hpp"
#include "game/scene/scene_start.hpp"
#include "game/scene/scene_world.hpp"
#include "game/scene/select_world.hpp"
#include "game/constant.hpp"
#include "game/mainwindow.hpp"

namespace game
{

  MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , view_(new QGraphicsView(this))
    , scene_(0)
  {
    // Init User Interface
    setWindowTitle(AMD_NAME);
    setWindowIcon(QIcon(":/core/life.png"));
    setCentralWidget(view_);
    view_->setFrameShape(QFrame::NoFrame);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(QCursor(Qt::BlankCursor));
    setFixedSize(AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);
    do_active_start_scene();
  }

  MainWindow::~MainWindow()
  {
  }


  void MainWindow::game_over()
  {
    if (scene_)
      scene_->deleteLater();

    scene_ = new scene::game_over();
    //FIXME: Reset the acquired life, reset a part of acquired eggs
    for (int i = 0; i < 90; ++i)
      player_->add_life();
    player_->save();
    connect(scene_, SIGNAL(sig_restart_game()), SLOT(do_active_start_scene()));
    view_->setScene(scene_);
  }

  void MainWindow::do_active_start_scene()
  {
    if (scene_)
      scene_->deleteLater();

    player_ = game_player_ptr();

    scene_ = new scene::scene_start();
    connect(scene_, SIGNAL(sig_return_pushed()), this, SLOT(do_active_menu_scene()));
    connect(scene_, SIGNAL(sig_escape_pushed()), qApp, SLOT(quit()));
    view_->setScene(scene_);
  }

  void MainWindow::do_active_menu_scene()
  {
    if (scene_)
      scene_->deleteLater();

    scene_ = new scene::scene_menu();
    connect(scene_, SIGNAL(sig_game_selected(game_player_ptr)),  this, SLOT(do_init_game(game_player_ptr)));
    connect(scene_, SIGNAL(sig_escape_pushed()),            qApp, SLOT(quit()));
    view_->setScene(scene_);
  }

  void MainWindow::do_init_game(game_player_ptr p)
  {
    player_ = p;
    do_active_world_select();
  }

  void MainWindow::do_active_world_select()
  {
    if (scene_)
      scene_->deleteLater();

    player_->current_world_item(world_item_ptr());

    scene_ = new scene::select_world(player_);
    connect(scene_, SIGNAL(sig_world_selected()),     this, SLOT(do_active_world_scene()));
    connect(scene_, SIGNAL(sig_quit_game_selected()), qApp, SLOT(quit()));
    view_->setScene(scene_);
  }

  void MainWindow::do_active_world_scene()
  {
    if (scene_)
      scene_->deleteLater();

    scene_ = new scene::world(player_);
    connect(scene_, SIGNAL(sig_return_selected()),    this, SLOT(do_active_world_select()));
    connect(scene_, SIGNAL(sig_level_selected()),     this, SLOT(do_active_level_scene()));
    connect(scene_, SIGNAL(sig_quit_game_selected()), qApp, SLOT(quit()));
    view_->setScene(scene_);
  }

  void MainWindow::do_active_level_scene()
  {
    if (scene_)
      scene_->deleteLater();

    scene_ = new scene::level(player_);
    connect(scene_, SIGNAL(sig_player_lose()),                      SLOT(do_player_lose()));
    connect(scene_, SIGNAL(sig_player_win(int, const QList<int>&)), SLOT(do_player_win(int, const QList<int>&)));
    connect(scene_, SIGNAL(sig_quit_game_selected()), qApp,         SLOT(quit()));
    view_->setScene(scene_);
  }

  void MainWindow::do_player_lose()
  {
    player_->remove_life();
    player_->save();
    if (player_->lifes())
      do_active_world_scene();
    else
      game_over();
  }

  void MainWindow::do_player_win(int id_door, const QList<int>& acquired_eggs)
  {
    player_->open_door(player_->current_world_item()->level(), id_door, true);
    for (int i = 0; i < acquired_eggs.size(); ++i)
      player_->acquired_egg(acquired_eggs.at(i));
    player_->save();
    do_active_world_scene();
  }

} // namespace game
