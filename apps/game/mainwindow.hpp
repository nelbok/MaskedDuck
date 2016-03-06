#ifndef GAME_MAINWINDOW_HPP
# define GAME_MAINWINDOW_HPP

# include <QMainWindow>

# include "game/data/player.hpp"

class QGraphicsView;
class QGraphicsScene;

namespace game
{

  /*!
   *  Main window of the game.\n
   *  Change the scene in function of the choice of the user.
   */

  class MainWindow : public QMainWindow
  {
      Q_OBJECT

    public:
      MainWindow(QWidget *parent = 0);
      ~MainWindow();

    private:
      game_player_ptr player_;
      QGraphicsView* view_;
      QGraphicsScene* scene_;

      void game_over();

    private slots:
      void do_active_start_scene();
      void do_active_menu_scene();
      void do_init_game(game_player_ptr p);
      void do_active_world_select();
      void do_active_world_scene();
      void do_active_level_scene();
      void do_player_lose();
      void do_player_win(int id_door, const QList<int>& acquired_eggs);

  };

} // namespace game

#endif // GAME_MAINWINDOW_HPP
