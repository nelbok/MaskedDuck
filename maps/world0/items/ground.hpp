#ifndef WORLD0_ITEMS_GROUND_HPP
# define WORLD0_ITEMS_GROUND_HPP

# include "core/items/block.hpp"

namespace world0
{
  
  class ground : public core::block
  {
    public:
      ground(const QPoint& pos, int width = 0, int height = 0);
  };

} // namespace world0

#endif // WORLD0_ITEMS_GROUND_HPP
