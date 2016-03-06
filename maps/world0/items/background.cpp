#include "background.hpp"

namespace world0
{
  
  background::background(const QPoint& pos, int width, int height)
    : core::block(":/world0/block/background.png", pos, width, height)
  {
  }

} // namespace world0
