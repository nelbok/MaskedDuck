#include "door.hpp"

namespace world1
{
  
  door::door(int id, const QPoint pos)
    : core::door(id, ":/world1/block/door.png", pos)
  {
  }
  
} // namespace world1
