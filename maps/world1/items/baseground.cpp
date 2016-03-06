#include "baseground.hpp"

namespace world1
{
  
  base_earth::base_earth(const QPoint& pos, int width, int height)
    : core::block(":/world1/block/earth.png", pos, width, height)
  {
  }

  base_ground::base_ground(const QPoint& pos, int width)
    : core::block(":/world1/block/ground.png", pos, width)
  {
  }

  base_platform::base_platform(const QPoint& pos, int width)
    : core::block(":/world1/block/platform.png", pos, width)
  {
  }

} // namespace world1
