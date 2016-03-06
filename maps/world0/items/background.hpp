#ifndef WORLD0_ITEMS_BACKGROUND_HPP
# define WORLD0_ITEMS_BACKGROUND_HPP

# include "core/items/block.hpp"

namespace world0
{
  
  class background : public core::block
  {
    public:
      background(const QPoint& pos, int width = 0, int height = 0);
  };

} // namespace world0

#endif // WORLD0_ITEMS_BACKGROUND_HPP
