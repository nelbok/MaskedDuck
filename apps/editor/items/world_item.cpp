#include <QPainter>

#include "editor/items/world_item.hpp"

Q_DECLARE_METATYPE(world_item_ptr)

namespace editor
{

  namespace items
  {

    world_item::world_item(world_item_ptr wi)
      : data_(wi)
    {
      switch (data_->type())
      {
        case core::world_item::NONE:
          img_ = QPixmap(":/editor/nothing.png");
          break;
        case core::world_item::RETURN:
          img_ = QPixmap(":/editor/return.png");
          break;
        case core::world_item::LEVEL:
          img_ = QPixmap(":/editor/level.png");
          break;
        case core::world_item::BOSS:
          img_ = QPixmap(":/editor/boss.png");
          break;
        case core::world_item::PNJ:
          img_ = QPixmap(":/editor/pnj.png");
          break;
      }

      QSize s = img_.size();
      rect_ = QRectF(-0.5 * s.width(), -0.5 * s.height(), s.width(), s.height());

      setData(Qt::UserRole, QVariant::fromValue(data_));
    }

    QRectF world_item::boundingRect() const
    {
      return rect_;
    }

    void world_item::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
    {
      p->drawPixmap(rect_.topLeft(), img_);
      if (data_->is_stage())
        if (stage_ptr s = data_->stage())
          p->drawText(rect_, Qt::AlignCenter, QString::number(s->id()));
    }

  } // namespace items

} // namespace editor
