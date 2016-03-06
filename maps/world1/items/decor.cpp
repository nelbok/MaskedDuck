#include "decor.hpp"

namespace world1
{
  
  decor_earth::decor_earth(const QPoint pos, int width, int height)
    : core::block(":/world1/block/decor_earth.png", pos, width, height)
  {
  }

  decor_ground::decor_ground(const QPoint& pos, int width)
    : core::block(":/world1/block/decor_ground.png", pos, width)
  {
  }

  decor_tree::decor_tree(const QPoint& pos)
    : core::block(":/world1/block/tree.png", pos)
  {
  }

} // namespace world1
