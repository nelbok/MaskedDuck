#ifndef WORLD1_ITEMS_FOREGROUND_HPP
# define WORLD1_ITEMS_FOREGROUND_HPP

# include "core/items/block.hpp"

namespace world1
{
  
  class fore_earth : public core::block
  {
    public:
      fore_earth(const QPoint pos, int width = 0, int height = 0);
  };

  class fore_ground : public core::block
  {
    public:
      fore_ground(const QPoint& pos, int width = 0);
  };

} // namespace world1

#endif // WORLD1_ITEMS_FOREGROUND_HPP
