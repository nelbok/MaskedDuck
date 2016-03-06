#ifndef GAME_ITEMS_DUCK_HPP
# define GAME_ITEMS_DUCK_HPP

# include <QGraphicsItem>

namespace game
{

  namespace items
  {

    /*!
     *  Duck's graphics item.
     */

    class duck : public QGraphicsItem
    {
      public:
        duck();

        QRectF boundingRect() const;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        QPainterPath shape() const;

        void go_to_right();
        void go_to_left();

      private:
        bool inversed_;
        QList<QPixmap> ducks_;
        int current_duck_;
    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_DUCK_HPP
