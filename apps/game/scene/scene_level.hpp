#ifndef GAME_SCENE_SCENE_LEVEL_HPP
# define GAME_SCENE_SCENE_LEVEL_HPP

# include <QGraphicsScene>

# include "graphics_engine/scene/scene_level.hpp"

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {
    class duck;
    class menu_item;
    class info_item;
  }

  namespace scene
  {

    /*!
     *  Level stage's graphics scene.
     */

    class level : public graphics_engine::scene_level
    {
      Q_OBJECT

      public:
        level(game_player_ptr p);
        ~level();

      protected:
        virtual void keyPressEvent(QKeyEvent*);
        virtual void keyReleaseEvent(QKeyEvent*);
        virtual void timerEvent(QTimerEvent*);

      private:
        void load();
        void kill_timer();
        void start_timer();

        // Methods to draw the widgets of the level.
        void draw_menu(int depth);
        void draw_info(int depth);
        void draw_lose(int depth);
        void draw_win(int depth);

        // Manage movement of the duck.
        bool can_move_to_left();
        bool can_move_to_right();
        bool can_move_to_bottom();
        bool can_move_to_top();
        void move_to_left();
        void move_to_right();
        void move_to_bottom();
        void move_to_top();
        void move_scene(qreal dx, qreal dy);

        // Methods for the management of the collisions.
        bool collide_with_obstacles(qreal dx, qreal dy);
        bool collide_with_death_items() const;
        QGraphicsItem* collide_with_door() const;
        QGraphicsItem* collide_with_life() const;
        QGraphicsItem* collide_with_egg() const;
        QGraphicsItem* collide(QGraphicsItem* obj, const QList<QGraphicsItem*>& list) const;

        game_player_ptr player_;
        items::duck* duck_;
        items::duck* duck_collide_;
        items::info_item* infoitem_;
        items::menu_item* menuitem_;

        bool left_pushed_;
        bool right_pushed_;
        bool space_pushed_;
        int jump_;
        bool lose_;
        bool win_;
        bool menu_;

        int timer_id_;

        QList<int> acquired_eggs_;
        bool acquired_life_;

      signals:
        /*! Signal emitted when the player lost.\n
         *  The player loses when he touches an element of the deaditem 's layer.
         */
        void sig_player_lose();
        /*! Signal emitted when the player clear the level.\n
         *  The player clean the level when he open a door.
         * \param id_door Identifying of the open door.
         * \param acquired_eggs List of acquired eggs during the level.
         */
        void sig_player_win(int id_door, const QList<int>& acquired_eggs);
        /*! Signal emitted when the player quit the game.\n
         *  The player quit the game when he select the option in the menu.
         */
        void sig_quit_game_selected();
    };

  } // namespace scene

} // namespace game

#endif // GAME_SCENE_SCENE_LEVEL_HPP
