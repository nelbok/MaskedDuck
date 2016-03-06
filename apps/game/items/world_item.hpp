#ifndef GAME_ITEMS_WORLD_ITEM_HPP
# define GAME_ITEMS_WORLD_ITEM_HPP

# include <QGraphicsItem>

# include "core/world_item.hpp"

namespace game
{

  namespace items
  {

    /*!
     *  World item's graphics item.\n
     *  Draw the specific item for a stage if exist.
     */

    class world_item : public QGraphicsItem
    {
      public:
        world_item(world_item_ptr wi);

        QRectF boundingRect() const;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

      private:
        QPixmap img_;
        QRectF rect_;
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_WORLD_ITEM_HPP
