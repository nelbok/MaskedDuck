#ifndef GAME_ITEMS_ROAD_HPP
# define GAME_ITEMS_ROAD_HPP

# include <QGraphicsItem>

namespace game
{

  namespace items
  {

    /*!
     *  Road's graphics item.
     */

    class road : public QGraphicsItem
    {
      public:
        road(int width);

        QRectF boundingRect() const;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

      private:
        QPixmap img_;
        int width_;
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_ROAD_HPP
