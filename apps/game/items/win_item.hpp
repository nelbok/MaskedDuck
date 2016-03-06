#ifndef GAME_ITEMS_WIN_ITEM_HPP
# define GAME_ITEMS_WIN_ITEM_HPP

# include <QGraphicsItemGroup>

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {

    /*!
     *  Win item's graphics item.\n
     */

    class win_item : public QGraphicsItemGroup
    {
      public:
        win_item(game_player_ptr p, const QList<int>& acquired_eggs, bool acquired_life);

      private:
        void init();

        game_player_ptr p_;
        const QList<int>& acquired_eggs_;
        bool acquired_life_;
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_WIN_ITEM_HPP
