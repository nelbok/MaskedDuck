#ifndef GAME_SCENE_SCENE_WORLD_HPP
# define GAME_SCENE_SCENE_WORLD_HPP

# include <QGraphicsScene>

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {
    class duck;
    class info_item;
    class menu_item;
    class status_level;
  }

  namespace scene
  {

    /*!
     *  World's graphics scene.\n
     */

    class world : public QGraphicsScene
    {
      Q_OBJECT

      public:
        world(game_player_ptr p);

      protected:
        virtual void keyPressEvent(QKeyEvent*);

      private:
        void load();

        // Methods to draw the widgets of the world.
        void draw_background(int depth);
        void draw_baseground(int depth);
        void draw_menu(int depth);
        void draw_info(int depth);
        void draw_status_level(int depth);

        void draw_road(QGraphicsItemGroup* group, QList<world_item_ptr>& already_draw, world_item_ptr current);
        void draw_world_item(QGraphicsItemGroup* group, world_item_ptr current);

        void move(int angle);

        game_player_ptr player_;
        world_ptr world_;
        items::duck* duck_;
        items::menu_item* menuitem_;
        items::info_item* infoitem_;
        items::status_level* statuslevel_;
        bool menu_;

      signals:
        /*! Signal emitted when the player quit the world.\n
         *  The player quit the world when he select a return's world item.
         */
        void sig_return_selected();
        /*! Signal emitted when the player choose a level.\n
         *  The player choose a level when he select a level's world item.
         */
        void sig_level_selected();
        /*! Signal emitted when the player quit the game.\n
         *  The player quit the game when he select the option in the menu.
         */
        void sig_quit_game_selected();

    };

  } // namespace scene

} // namespace game

#endif // GAME_SCENE_SCENE_WORLD_HPP
