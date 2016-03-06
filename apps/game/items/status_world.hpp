#ifndef GAME_ITEMS_STATUS_WORLD_HPP
# define GAME_ITEMS_STATUS_WORLD_HPP

# include <QGraphicsItemGroup>

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {

    /*!
     *  Status world's graphics item.\n
     *  Show a description of the world with the life and eggs collected.
     */

    class status_world : public QGraphicsItemGroup
    {
      public:
        status_world(game_player_ptr p);

        void update_text();

      private:
        void init();

        game_player_ptr p_;
        QGraphicsTextItem* world_;
        QGraphicsTextItem* eggs_;
        QGraphicsTextItem* lifes_;
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_STATUS_WORLD_HPP
