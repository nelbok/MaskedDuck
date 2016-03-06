#include <QPainter>

#include "game/items/duck.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace items
  {

    duck::duck()
      : inversed_(false)
      , current_duck_(0)
    {
      ducks_.append(QPixmap(":/game/duck/duck-1.png"));
      ducks_.append(QPixmap(":/game/duck/duck-2.png"));
      ducks_.append(QPixmap(":/game/duck/duck-3.png"));
    }

    QRectF duck::boundingRect() const
    {
      return QRectF(-15, -15, 30, 30);
    }

    void duck::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
    {
      p->drawPixmap(-15, -15, ducks_.at(current_duck_));

      ++current_duck_;
      if (current_duck_ == ducks_.count())
        current_duck_ = 0;
    }

    QPainterPath duck::shape() const
    {
      QPainterPath p;
      p.addRect(-10, -15, 20, 30);
      return p;
    }


    void duck::go_to_right()
    {
      if (inversed_)
      {
        inversed_ = false;
        setTransform(QTransform::fromScale(-1, 1), true);
      }
    }

    void duck::go_to_left()
    {
      if (not inversed_)
      {
        inversed_ = true;
        setTransform(QTransform::fromScale(-1, 1), true);
      }
    }

  } // namespace items

} // namespace game
