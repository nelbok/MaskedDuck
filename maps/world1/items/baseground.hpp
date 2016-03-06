#ifndef WORLD1_ITEMS_BASEGROUND_HPP
# define WORLD1_ITEMS_BASEGROUND_HPP

# include "core/items/block.hpp"

namespace world1
{
  
  class base_earth : public core::block
  {
    public:
      base_earth(const QPoint& pos, int width = 0, int height = 0);
  };

  class base_ground : public core::block
  {
    public:
      base_ground(const QPoint& pos, int width = 0);
  };

  class base_platform : public core::block
  {
    public:
      base_platform(const QPoint& pos, int width = 0);
  };

} // namespace world1

#endif // WORLD1_ITEMS_BASEGROUND_HPP
