#include <QPainter>

#include "game/items/road.hpp"

namespace game
{

  namespace items
  {

    road::road(int width)
      : img_(QPixmap(":/game/world/road.png"))
      , width_(width)
    {
    }

    QRectF road::boundingRect() const
    {
      return QRectF(0, -4, width_, 8);
    }

    void road::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
    {
      p->drawTiledPixmap(boundingRect(), img_);
    }

  } // namespace items

} // namespace game
