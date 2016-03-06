#include "door.hpp"

namespace world0
{
  
  door::door(int id, const QPoint& pos, int width, int height)
    : core::door(id, ":/world0/block/door.png", pos, width, height)
  {
  }
  
} // namespace world0
