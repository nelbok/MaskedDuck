#include "world0.hpp"

namespace world0
{

  world0::world0()
  {
    world_item_ptr wi1 = world_item_ptr(new core::world_item(QPoint(420, 300), true));
    add_world_item(wi1);
  }


  int world0::id() const
  {
    return 0;
  }

  const QString world0::name() const
  {
    return "Duck city";
  }

  const QPixmap world0::pixmap() const
  {
    return QPixmap(":/world0/world.png");
  }

  const QPoint world0::pos() const
  {
    return QPoint(350, 250);
  }

  const QPoint world0::global_pos() const
  {
    return QPoint(700, 500);
  }

} // namespace world0
