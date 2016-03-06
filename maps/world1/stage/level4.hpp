#ifndef WORLD1_LEVEL4_HPP
# define WORLD1_LEVEL4_HPP

# include <QList>

# include "core/stage/level.hpp"

namespace world1
{

  class level4 : public core::level
  {
    public:
      level4();

      virtual int id() const;
      virtual const QString name() const;

      virtual const QPoint start_position() const;
      virtual const QList<core::block*> background() const;
      virtual const QList<core::block*> decor() const;
      virtual const QList<core::block*> signs() const;
      virtual const QList<core::block*> doors() const;
      virtual const QList<core::block*> eggs(const QList<bool>& already_acquired) const;
      virtual const QList<core::block*> lifes(const QList<bool>& already_acquired) const;
      virtual const QList<core::block*> baseground() const;
      virtual const QList<core::block*> foreground() const;
      virtual const QList<core::block*> death_items() const;
  };

} // namespace world1

#endif // WORLD1_LEVEL4_HPP
