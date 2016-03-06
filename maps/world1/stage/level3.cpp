#include "items/all.hpp"

#include "level3.hpp"

namespace world1
{

  level3::level3()
  {

  }


  int level3::id() const
  {
    return 3;
  }

  const QString level3::name() const
  {
    return "Level 3";
  }


  const QPoint level3::start_position() const
  {
    return QPoint(15, 1650);
  }

  const QList<core::block*> level3::background() const
  {
    QList<core::block*> l;

    l.append(new world1::background(QPoint(0, 0), 800));

    return l;
  }

  const QList<core::block*> level3::decor() const
  {
    return QList<core::block*>();
  }

  const QList<core::block*> level3::signs() const
  {
    return QList<core::block*>();
  }

  const QList<core::block*> level3::doors() const
  {
    QList<core::block*> l;

    l.append(new world1::door(1, QPoint(550, 1650)));

    return l;
  }

  const QList<core::block*> level3::eggs(const QList<bool>&) const
  {
    return QList<core::block*>();
  }

  const QList<core::block*> level3::lifes(const QList<bool>&) const
  {
    return QList<core::block*>();
  }

  const QList<core::block*> level3::baseground() const
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

  const QList<core::block*> level3::foreground() const
  {
    QList<core::block*> l;

    return l;
  }

  const QList<core::block*> level3::death_items() const
  {
    QList<core::block*> l;

    return l;
  }

} // namespace world1
