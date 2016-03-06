#include "foreground.hpp"

namespace world1
{
  
  fore_earth::fore_earth(const QPoint pos, int width, int height)
    : core::block(":/world1/block/fore_earth.png", pos, width, height)
  {
  }

  fore_ground::fore_ground(const QPoint& pos, int width)
    : core::block(":/world1/block/fore_ground.png", pos, width)
  {
  }

} // namespace world1
