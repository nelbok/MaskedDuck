#include "world2.hpp"

namespace world2
{

  world2::world2()
  {
    world_item_ptr wi1 = world_item_ptr(new core::world_item(QPoint(300, 350), true));
    add_world_item(wi1);
  }


  int world2::id() const
  {
    return 2;
  }

  const QString world2::name() const
  {
    return "The mountain of wolves";
  }

  const QPixmap world2::pixmap() const
  {
    return QPixmap(":/world2/world.png");
  }

  const QPoint world2::pos() const
  {
    return QPoint(220, 180);
  }

  const QPoint world2::global_pos() const
  {
    return QPoint(600, 300);
  }

} // namespace world2
