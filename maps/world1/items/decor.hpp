#ifndef WORLD1_ITEMS_DECOR_HPP
# define WORLD1_ITEMS_DECOR_HPP

# include "core/items/block.hpp"

namespace world1
{
  
  class decor_earth : public core::block
  {
    public:
      decor_earth(const QPoint pos, int width = 0, int height = 0);
  };

  class decor_ground : public core::block
  {
    public:
      decor_ground(const QPoint& pos, int width = 0);
  };

  class decor_tree : public core::block
  {
    public:
      decor_tree(const QPoint& pos);
  };

} // namespace world1

#endif // WORLD1_ITEMS_DECOR_HPP
