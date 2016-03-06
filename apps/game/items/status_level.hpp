#ifndef GAME_ITEMS_STATUS_LEVEL_HPP
# define GAME_ITEMS_STATUS_LEVEL_HPP

# include <QGraphicsItemGroup>

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {

    /*!
     *  Status level's graphics item.\n
     *  Show a description of the level with the life and eggs collected.
     */

    class status_level : public QGraphicsItemGroup
    {
      public:
        status_level(game_player_ptr p);

      private:
        void init();

        game_player_ptr p_;
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_STATUS_LEVEL_HPP
