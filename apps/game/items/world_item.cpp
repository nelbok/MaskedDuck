#include <QPainter>

#include "game/items/world_item.hpp"

namespace game
{

  namespace items
  {

    world_item::world_item(world_item_ptr wi)
    {
      switch (wi->type())
      {
        case core::world_item::NONE:
          img_ = QPixmap(":/game/world/nothing.png");
          break;
        case core::world_item::RETURN:
          img_ = QPixmap(":/game/world/return.png");
          break;
        case core::world_item::LEVEL:
          img_ = QPixmap(":/game/world/level.png");
          break;
        case core::world_item::BOSS:
          img_ = QPixmap(":/game/world/boss.png");
          break;
        case core::world_item::PNJ:
          img_ = QPixmap(":/game/world/pnj.png");
          break;
      }

      QSize s = img_.size();
      rect_ = QRectF(-0.5 * s.width(), -0.5 * s.height(), s.width(), s.height());

    }

    QRectF world_item::boundingRect() const
    {
      return rect_;
    }

    void world_item::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
    {
      p->drawPixmap(rect_.topLeft(), img_);
    }

  } // namespace items

} // namespace game
