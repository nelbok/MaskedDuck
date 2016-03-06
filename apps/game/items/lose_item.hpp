#ifndef GAME_ITEMS_LOSE_ITEM_HPP
# define GAME_ITEMS_LOSE_ITEM_HPP

# include <QGraphicsItemGroup>

namespace game
{

  namespace items
  {

    /*!
     *  Lose's graphics item.
     */

    class lose_item : public QGraphicsItemGroup
    {
      public:
        lose_item();

      private:
        void init();
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_LOSE_ITEM_HPP
