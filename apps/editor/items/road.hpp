#ifndef EDITOR_ITEMS_ROAD_HPP
# define EDITOR_ITEMS_ROAD_HPP

# include <QGraphicsItem>

# include "core/world_item.hpp"

namespace editor
{

  namespace items
  {

    /*!
     *  Road's graphics item.
     */

    class road : public QGraphicsItem
    {
      public:
        road(world_item_ptr w1, world_item_ptr w2, int id_door, int width);

        QRectF boundingRect() const;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

      private:
        QPixmap img_;
        world_item_ptr w1_;
        world_item_ptr w2_;
        int id_door_;
        int width_;
    };

  } // namespace items

} // namespace editor

#endif // EDITOR_ITEMS_ROAD_HPP
