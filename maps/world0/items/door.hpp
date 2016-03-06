#ifndef WORLD0_ITEMS_DOOR_HPP
# define WORLD0_ITEMS_DOOR_HPP

# include "core/items/door.hpp"

namespace world0
{
  
  class door : public core::door
  {
    public:
      door(int id, const QPoint& pos, int width = 0, int height = 0);
  };
  
} // namespace world0

#endif // WORLD0_ITEMS_DOOR_HPP
