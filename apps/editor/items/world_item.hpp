#ifndef EDITOR_ITEMS_WORLD_ITEM_HPP
# define EDITOR_ITEMS_WORLD_ITEM_HPP

# include <QGraphicsItem>

# include "core/world_item.hpp"

namespace editor
{

  namespace items
  {

    /*!
     *  World Item's graphics item.
     */

    class world_item : public QGraphicsItem
    {
      public:
        world_item(world_item_ptr wi);

        QRectF boundingRect() const;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

      private:
        world_item_ptr data_;
        QPixmap img_;
        QRectF rect_;
    };

  } // namespace items

} // namespace editor

#endif // EDITOR_ITEMS_WORLD_ITEM_HPP
