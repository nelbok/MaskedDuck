#include "core/world.hpp"

namespace core
{

  world::world()
  {
  }

  world::~world()
  {
  }

  const world_item_ptr world::return_item() const
  {
    for (int i = 0; i < world_items_.size(); ++i)
    {
      world_item_ptr wi = world_items_.at(i);
      if (wi->type() == world_item::RETURN)
        return wi;
    }

    return world_item_ptr();
  }

  const QList<world_item_ptr>& world::world_items() const
  {
    Q_ASSERT(not world_items_.isEmpty());
    return world_items_;
  }


  void world::add_world_item(world_item_ptr wi)
  {
    // Only one return item can exist in a world.
    Q_ASSERT(not (wi->type() == world_item::RETURN and return_item()));
    world_items_.append(wi);
  }

  void world::remove_world_item(world_item_ptr wi)
  {
    Q_ASSERT(world_items_.contains(wi));
    core::world_item::clear_connexions(wi);
    world_items_.removeAll(wi);
  }

  void world::clear_world_items()
  {
    world_items_.clear();
  }

} // namespace core
