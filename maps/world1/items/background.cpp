#include "background.hpp"

namespace world1
{
  
  background::background(const QPoint& pos, int width, int height)
    : core::block(":/world1/block/background.png", pos, width, height)
  {
  }

} // namespace world1
