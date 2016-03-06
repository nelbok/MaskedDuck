#ifndef CORE_ITEMS_DOOR_HPP
# define CORE_ITEMS_DOOR_HPP

# include "core/items/block.hpp"

namespace core
{
  
  /*!
   *  Door block.\n
   * \param id The identifying of the door.
   */

  class door : public core::block
  {
    public:
      door(int id, const QString& img, const QPoint& pos, int width = 0, int height = 0);
  };
  
} // namespace core

#endif // CORE_ITEMS_DOOR_HPP
