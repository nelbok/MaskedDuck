#include "death_items.hpp"

namespace world1
{
  
  death_chocolate::death_chocolate(const QPoint pos, int width)
    : core::block(":/world1/block/death_chocolate.png", pos, width)
  {
  }

  QPainterPath death_chocolate::shape() const
  {
    QPainterPath p;
    QRectF r = boundingRect();
    r.setY(r.y() + 20);
    p.addRect(r);
    return p;
  }

} // namespace world1
