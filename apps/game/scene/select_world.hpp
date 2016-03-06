#ifndef GAME_SCENE_SELECT_WORLD_HPP
# define GAME_SCENE_SELECT_WORLD_HPP

# include <QGraphicsScene>
# include <QMap>

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {
    class info_item;
    class menu_item;
    class status_world;
  }

  namespace scene
  {

    /*!
     *  Select world's graphics scene.\n
     *  Display all the world.
     */

    class select_world : public QGraphicsScene
    {
      Q_OBJECT

      public:
        select_world(game_player_ptr p);

      protected:
        virtual void keyPressEvent(QKeyEvent*);

      private:
        void load();

        // Methods to draw the widgets of the select world.
        void draw_background(int depth);
        void draw_baseground(int depth);
        void draw_menu(int depth);
        void draw_info(int depth);
        void draw_status_world(int depth);

        void update_selection();

        game_player_ptr player_;
        map_ptr map_;
        QMap<QGraphicsItem*, world_ptr> worlds_;
        items::info_item* info_item_;
        items::menu_item* menuitem_;
        items::status_world* statusworld_;
        bool menu_;

      signals:
        /*! Signal emitted when the player choose a world.\n
         *  The player choose a world when he select the option in the menu.
         */
        void sig_world_selected();
        /*! Signal emitted when the player quit the game.\n
         *  The player quit the game when he select the option in the menu.
         */
        void sig_quit_game_selected();
    };

  } // namespace scene

} // namespace game

#endif // GAME_SCENE_SELECT_WORLD_HPP
