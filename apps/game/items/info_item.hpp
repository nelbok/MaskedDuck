#ifndef GAME_ITEMS_INFO_ITEM_HPP
# define GAME_ITEMS_INFO_ITEM_HPP

# include <QGraphicsItemGroup>

# include "game/data/player.hpp"

namespace game
{

  namespace items
  {

    /*!
     *  Information's graphics item.\n
     *  Display the statistics and the place where is the duck.
     */

    class info_item : public QGraphicsItemGroup
    {
      public:
        info_item(game_player_ptr p);

        void update_text();

      private:
        void init();

        QGraphicsTextItem* life_text_;
        QGraphicsTextItem* place_text_;
        QGraphicsTextItem* egg_text_;
        game_player_ptr player_;
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_INFO_ITEM_HPP
