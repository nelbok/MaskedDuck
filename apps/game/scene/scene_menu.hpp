#ifndef GAME_SCENE_SCENE_MENU_HPP
# define GAME_SCENE_SCENE_MENU_HPP

# include <QGraphicsScene>

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {
    class status_game;
  }

  namespace scene
  {

    /*!
     *  Menu's graphics scene.\n
     *  Display the three party in the game.
     */

    class scene_menu : public QGraphicsScene
    {
      Q_OBJECT

      public:
        scene_menu();

      protected:
        void keyPressEvent(QKeyEvent* e);

      private:
        void load();

        // Methods to draw the widgets of the menu.
        void draw_background(int depth);
        void draw_info_top(int depth);
        void draw_info_game(int depth);
        void draw_info_save_dir(int depth);

        void reset_info_game();
        void update_info_game(int index);

        items::status_game* current_;
        QList<items::status_game*> infos_game_;

      signals:
        /*! Signal emitted when the player select a game.\n
         * \param game Game instance selected by the player.
         */
        void sig_game_selected(game_player_ptr game);
        /*! Signal emitted when the player push escape.
         */
        void sig_escape_pushed();

    };

  } // namespace scene

} // namespace game

#endif // GAME_SCENE_SCENE_MENU_HPP
