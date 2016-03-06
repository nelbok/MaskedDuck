#ifndef CORE_WORLD_HPP
# define CORE_WORLD_HPP

# include <QList>
# include <QPixmap>

# include "core/no_copy.hpp"
# include "core/world_item.hpp"

namespace core
{

  /*!
   *  Class abstracted from a world. \n
   *  Contains a list of elements composing the world map.
   */

  class world : public no_copy
  {
    public:
      world();
      virtual ~world();

      // Gets all the attributes
      virtual int id() const = 0;
      virtual const QString name() const = 0;
      virtual const QPixmap pixmap() const = 0;
      virtual const QPoint pos() const = 0;
      virtual const QPoint global_pos() const = 0;

      /*! The return item allows the connection between all the worlds.\n
       *  Only one return item can exist in a world.
       */
      const world_item_ptr return_item() const;
      const QList<world_item_ptr>& world_items() const;

    protected:
      // Methods for the list of elements composing the world map.
      void add_world_item(world_item_ptr);
      void remove_world_item(world_item_ptr);
      void clear_world_items();

    private:
      QList<world_item_ptr> world_items_;

  };

} // namespace core

typedef QSharedPointer<core::world> world_ptr;

#endif // CORE_WORLD_HPP
