#include <QPainter>

#include "editor/items/road.hpp"

Q_DECLARE_METATYPE(world_item_ptr)

namespace editor
{

  namespace items
  {

    road::road(world_item_ptr w1, world_item_ptr w2, int id_door, int width)
      : img_(QPixmap(":/editor/road.png"))
      , w1_(w1)
      , w2_(w2)
      , id_door_(id_door)
      , width_(width)
    {
      setData(Qt::UserRole + 1, QVariant::fromValue(w1));
      setData(Qt::UserRole + 2, QVariant::fromValue(w2));
    }

    QRectF road::boundingRect() const
    {
      return QRectF(0, -4, width_, 8);
    }

    void road::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
    {
      const QRectF& r = boundingRect();
      p->drawTiledPixmap(boundingRect(), img_);
      if (id_door_)
      {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::white);
        p->setBrush(brush);
        p->drawEllipse(r.center(), 7, 7);
        p->drawText(r, Qt::AlignCenter, QString::number(id_door_));
      }
    }

  } // namespace items

} // namespace editor
