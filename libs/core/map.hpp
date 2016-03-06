#ifndef CORE_MAP_HPP
# define CORE_MAP_HPP

# include <QList>

# include "core/no_copy.hpp"
# include "core/world.hpp"

namespace core
{

  /*!
   *  This class gets all the worlds which are in the
   *  maps directory next to the executable.
   */

  class map : public no_copy
  {
    public:
      map();
      virtual ~map();

      /*! Get all the worlds */
      const QList<world_ptr>& worlds() const;

    private:
      /*! Load all the worlds */
      void load_worlds();
      void load_world(const QString& name);

      QList<world_ptr> worlds_;
  };

} // namespace core

typedef QSharedPointer<core::map> map_ptr;

#endif // CORE_MAP_HPP
