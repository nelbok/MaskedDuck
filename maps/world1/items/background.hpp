#ifndef WORLD1_ITEMS_BACKGROUND_HPP
# define WORLD1_ITEMS_BACKGROUND_HPP

# include "core/items/block.hpp"

namespace world1
{
  
  class background : public core::block
  {
    public:
      background(const QPoint& pos, int width = 0, int height = 0);
  };

} // namespace world1

#endif // WORLD1_ITEMS_BACKGROUND_HPP
