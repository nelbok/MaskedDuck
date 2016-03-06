#include "ground.hpp"

namespace world0
{
  
  ground::ground(const QPoint& pos, int width, int height)
    : core::block(":/world0/block/ground.png", pos, width, height)
  {
  }

} // namespace world0
