#include "door.hpp"

namespace core
{
  
  door::door(int id, const QString& img, const QPoint& pos, int width, int height)
    : core::block(img, pos, width, height)
  {
    setData(Qt::UserRole, QVariant(id));
  }


} // namespace core
