#ifndef GAME_ITEMS_STATUS_GAME_HPP
# define GAME_ITEMS_STATUS_GAME_HPP

# include <QGraphicsItemGroup>

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {

    /*!
     *  Status game's graphics item.\n
     *  Show a description of the game with the life and eggs collected.
     */

    class status_game : public QGraphicsItemGroup
    {
      public:
        status_game(game_player_ptr p);

        game_player_ptr player() const;

        void reinit();
        void change_option();
        bool reset_mode() const;

        void focus();
        void unfocus();

      private:
        void init();
        void update_duck();

        game_player_ptr p_;
        QGraphicsRectItem* focus_rect_;
        QGraphicsItemGroup* new_game_group_;
        QGraphicsItemGroup* continue_group_;
        QGraphicsItem* duck_item_;
        bool reset_mode_;
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_STATUS_GAME_HPP
