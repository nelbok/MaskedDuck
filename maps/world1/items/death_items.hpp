#ifndef WORLD1_ITEMS_DEATH_ITEMS_HPP
# define WORLD1_ITEMS_DEATH_ITEMS_HPP

# include "core/items/block.hpp"

namespace world1
{
  
  class death_chocolate : public core::block
  {
    public:
      death_chocolate(const QPoint pos, int width = 0);

      QPainterPath shape() const;
  };

} // namespace world1

#endif // WORLD1_ITEMS_DEATH_ITEMS_HPP
