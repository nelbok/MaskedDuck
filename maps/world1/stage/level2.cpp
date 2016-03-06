#include "items/all.hpp"

#include "level2.hpp"

namespace world1
{

  level2::level2()
  {

  }


  int level2::id() const
  {
    return 2;
  }

  const QString level2::name() const
  {
    return "The wolf forest";
  }


  const QPoint level2::start_position() const
  {
    return QPoint(15, 1650);
  }

  const QList<core::block*> level2::background() const
  {
    QList<core::block*> l;

    l.append(new world1::background(QPoint(0, 0), 800));

    return l;
  }

  const QList<core::block*> level2::decor() const
  {
    return QList<core::block*>();
  }

  const QList<core::block*> level2::signs() const
  {
    return QList<core::block*>();
  }

  const QList<core::block*> level2::doors() const
  {
    QList<core::block*> l;

    l.append(new world1::door(1, QPoint(550, 1650)));
    l.append(new world1::door(2, QPoint(650, 1650)));

    return l;
  }

  const QList<core::block*> level2::eggs(const QList<bool>&) const
  {
    return QList<core::block*>();
  }

  const QList<core::block*> level2::lifes(const QList<bool>&) const
  {
    return QList<core::block*>();
  }

  const QList<core::block*> level2::baseground() const
  {
    QList<core::block*> l;

    //begin
    l.append(new world1::base_ground(QPoint(0, 1750), 200));
    l.append(new world1::base_ground(QPoint(200, 1700), 200));
    l.append(new world1::base_earth(QPoint(200, 1750), 200));
    l.append(new world1::base_ground(QPoint(400, 1750), 100));
    l.append(new world1::base_ground(QPoint(500, 1700), 200));
    l.append(new world1::base_earth(QPoint(500, 1750), 200));
    l.append(new world1::base_ground(QPoint(850, 1700), 100));
    l.append(new world1::base_earth(QPoint(850, 1750), 100));

    return l;
  }

  const QList<core::block*> level2::foreground() const
  {
    QList<core::block*> l;

    return l;
  }

  const QList<core::block*> level2::death_items() const
  {
    QList<core::block*> l;

    return l;
  }

} // namespace world1
