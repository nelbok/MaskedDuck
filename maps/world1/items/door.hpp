#ifndef WORLD1_ITEMS_DOOR_HPP
# define WORLD1_ITEMS_DOOR_HPP

# include "core/items/door.hpp"

namespace world1
{
  
  class door : public core::door
  {
    public:
      door(int id, const QPoint pos);
  };
  
} // namespace world1

#endif // WORLD1_ITEMS_DOOR_HPP
