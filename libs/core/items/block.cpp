#include <QPainter>

#include "block.hpp"

namespace core
{

  block::block(const QString& img, const QPoint& pos, int width, int height)
    : width_(width)
    , height_(height)
    , img_(QPixmap(img))
  {
    setPos(pos);
    if (width_ == 0)
      width_ = img_.width();
    if (height_ == 0)
      height_ = img_.height();
  }


  QRectF block::boundingRect() const
  {
    return QRectF(0, 0, width_, height_);
  }

  void block::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
  {
    p->drawTiledPixmap(0, 0, width_, height_, img_);
  }

  QPainterPath block::shape() const
  {
    QPainterPath p;
    p.addRect(0, 0, width_, height_);
    return p;
  }

} // namespace core
