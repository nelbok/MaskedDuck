#include <QCoreApplication>

#include "core/items/egg.hpp"
#include "core/items/life.hpp"
#include "items/all.hpp"

#include "level1.hpp"

namespace world1
{

  level1::level1()
  {

  }


  int level1::id() const
  {
    return 1;
  }

  const QString level1::name() const
  {
    return QCoreApplication::translate("world1", "The entrance of the forest");
  }


  const QPoint level1::start_position() const
  {
    return QPoint(15, 1650);
  }

  const QList<core::block*> level1::background() const
  {
    QList<core::block*> l;

    l.append(new world1::background(QPoint(0, 0), 800));

    return l;
  }

  const QList<core::block*> level1::decor() const
  {
    QList<core::block*> l;

    //block 1
    l.append(new world1::decor_ground(QPoint(400, 1650), 200));
    l.append(new world1::decor_earth(QPoint(400, 1700), 200));
    l.append(new world1::decor_ground(QPoint(650, 1500), 200));
    l.append(new world1::decor_earth(QPoint(600, 1550), 200, 250));
    l.append(new world1::decor_earth(QPoint(800, 1550), 50, 100));
    l.append(new world1::decor_earth(QPoint(850, 1500), 150, 200));

    //block 2
    l.append(new world1::decor_earth(QPoint(1450, 1500)));
    l.append(new world1::decor_ground(QPoint(1500, 1250), 100));
    l.append(new world1::decor_ground(QPoint(1700, 1250), 100));
    l.append(new world1::decor_ground(QPoint(1900, 1250), 100));
    l.append(new world1::decor_ground(QPoint(2100, 1250), 100));
    l.append(new world1::decor_earth(QPoint(1500, 1300), 700, 450));

    //block 3
    l.append(new world1::decor_ground(QPoint(2800, 1250), 200));
    l.append(new world1::decor_ground(QPoint(3400, 1250), 200));
    l.append(new world1::decor_ground(QPoint(4000, 1300), 100));
    l.append(new world1::decor_ground(QPoint(4100, 1350), 100));
    l.append(new world1::decor_earth(QPoint(2400, 1300), 200, 450));
    l.append(new world1::decor_earth(QPoint(2600, 1300), 200, 400));
    l.append(new world1::decor_earth(QPoint(2800, 1300), 200, 350));
    l.append(new world1::decor_earth(QPoint(3000, 1300), 200, 300));
    l.append(new world1::decor_earth(QPoint(3200, 1300), 200, 250));
    l.append(new world1::decor_earth(QPoint(3400, 1300), 200, 200));
    l.append(new world1::decor_earth(QPoint(3600, 1300), 200, 150));
    l.append(new world1::decor_earth(QPoint(3800, 1300), 200, 100));
    l.append(new world1::decor_earth(QPoint(4000, 1350), 100));

    //block 4
    l.append(new world1::decor_earth(QPoint(4200, 1650), 1200, 100));
    l.append(new world1::decor_ground(QPoint(5400, 1450), 100));
    l.append(new world1::decor_earth(QPoint(5400, 1500), 100, 250));
    l.append(new world1::decor_ground(QPoint(5500, 1500), 100));
    l.append(new world1::decor_earth(QPoint(5500, 1550), 100, 200));
    l.append(new world1::decor_ground(QPoint(5600, 1550), 100));
    l.append(new world1::decor_earth(QPoint(5600, 1600), 100, 150));
    l.append(new world1::decor_ground(QPoint(5700, 1600), 100));
    l.append(new world1::decor_earth(QPoint(5700, 1650), 100, 100));
    l.append(new world1::decor_ground(QPoint(5800, 1650), 100));
    l.append(new world1::decor_earth(QPoint(5800, 1700), 100));
    l.append(new world1::decor_ground(QPoint(5900, 1700), 100));

    //block 6
    l.append(new world1::decor_ground(QPoint(6900, 1700), 50));
    l.append(new world1::decor_ground(QPoint(6950, 1650), 150));
    l.append(new world1::decor_earth(QPoint(6950, 1700), 150));
    l.append(new world1::decor_ground(QPoint(7150, 1600)));
    l.append(new world1::decor_ground(QPoint(7250, 1500)));
    l.append(new world1::decor_ground(QPoint(7350, 1400)));
    l.append(new world1::decor_ground(QPoint(7550, 1250)));
    l.append(new world1::decor_ground(QPoint(7650, 1150)));
    l.append(new world1::decor_ground(QPoint(7700, 1100)));
    l.append(new world1::decor_ground(QPoint(7750, 1050)));
    l.append(new world1::decor_earth(QPoint(7750, 1100)));
    l.append(new world1::decor_ground(QPoint(7800, 1000)));
    l.append(new world1::decor_earth(QPoint(7800, 1050)));
    l.append(new world1::decor_ground(QPoint(7850, 950)));
    l.append(new world1::decor_earth(QPoint(7850, 1000), 50, 100));

    //Tree
    l.append(new world1::decor_tree(QPoint(300, 1500)));
    l.append(new world1::decor_tree(QPoint(400, 1450)));
    l.append(new world1::decor_tree(QPoint(500, 1450)));
    l.append(new world1::decor_tree(QPoint(750, 1300)));
    l.append(new world1::decor_tree(QPoint(850, 1250)));
    l.append(new world1::decor_tree(QPoint(950, 1250)));
    l.append(new world1::decor_tree(QPoint(1150, 1150)));
    l.append(new world1::decor_tree(QPoint(1380, 1050)));
    l.append(new world1::decor_tree(QPoint(1440, 1050)));
    l.append(new world1::decor_tree(QPoint(1600, 1050)));
    l.append(new world1::decor_tree(QPoint(1680, 1050)));
    l.append(new world1::decor_tree(QPoint(1750, 1050)));
    l.append(new world1::decor_tree(QPoint(1900, 1050)));
    l.append(new world1::decor_tree(QPoint(1990, 1050)));
    l.append(new world1::decor_tree(QPoint(2080, 1050)));
    l.append(new world1::decor_tree(QPoint(2450, 1050)));
    l.append(new world1::decor_tree(QPoint(2570, 1050)));
    l.append(new world1::decor_tree(QPoint(2620, 1050)));
    l.append(new world1::decor_tree(QPoint(2750, 1050)));
    l.append(new world1::decor_tree(QPoint(2820, 1050)));
    l.append(new world1::decor_tree(QPoint(2910, 1050)));
    l.append(new world1::decor_tree(QPoint(3050, 1050)));
    l.append(new world1::decor_tree(QPoint(3170, 1050)));
    l.append(new world1::decor_tree(QPoint(3280, 1050)));
    l.append(new world1::decor_tree(QPoint(3400, 1050)));
    l.append(new world1::decor_tree(QPoint(3480, 1050)));
    l.append(new world1::decor_tree(QPoint(3550, 1050)));
    l.append(new world1::decor_tree(QPoint(3700, 1050)));
    l.append(new world1::decor_tree(QPoint(3780, 1050)));
    l.append(new world1::decor_tree(QPoint(6600, 1550)));
    l.append(new world1::decor_tree(QPoint(6730, 1550)));


    return l;
  }

  const QList<core::block*> level1::signs() const
  {
    QList<core::block*> l;

    //Information
    l.append(new world1::sign_move(QPoint(150, 1700)));
    l.append(new world1::sign_jump(QPoint(250, 1650)));
    l.append(new world1::sign_get(QPoint(1800, 1650)));
    l.append(new world1::sign_danger(QPoint(4150, 1350)));
    l.append(new world1::sign_danger(QPoint(4450, 1350)));
    l.append(new world1::sign_danger(QPoint(4750, 1350)));
    l.append(new world1::sign_danger(QPoint(5050, 1350)));
    l.append(new world1::sign_danger(QPoint(6350, 1700)));
    l.append(new world1::sign_open(QPoint(6950, 1700)));

    //Direction
    l.append(new world1::sign_up_right(QPoint(700, 1700)));
    l.append(new world1::sign_up_left(QPoint(900, 1600)));
    l.append(new world1::sign_up_right(QPoint(650, 1475)));
    l.append(new world1::sign_right(QPoint(1400, 1200)));
    l.append(new world1::sign_down_right(QPoint(1625, 1200)));
    l.append(new world1::sign_right(QPoint(2100, 1700)));
    l.append(new world1::sign_up_right(QPoint(2500, 1700)));
    l.append(new world1::sign_right(QPoint(4300, 1350)));
    l.append(new world1::sign_down_right(QPoint(5300, 1350)));
    l.append(new world1::sign_right(QPoint(6050, 1700)));

    return l;
  }

  const QList<core::block*> level1::doors() const
  {
    QList<core::block*> l;

    l.append(new world1::door(1, QPoint(7000, 1700)));

    return l;
  }

  const QList<core::block*> level1::eggs(const QList<bool>& already_acquired) const
  {
    QList<core::block*> l;

    if (already_acquired.isEmpty() or not already_acquired.at(0))
      l.append(new core::egg(1, QPoint(1465, 1530)));
    if (already_acquired.isEmpty() or not already_acquired.at(1))
      l.append(new core::egg(2, QPoint(1865, 1680)));
    if (already_acquired.isEmpty() or not already_acquired.at(2))
      l.append(new core::egg(3, QPoint(3800, 1230)));
    if (already_acquired.isEmpty() or not already_acquired.at(3))
      l.append(new core::egg(4, QPoint(5300, 1380)));
    if (already_acquired.isEmpty() or not already_acquired.at(4))
      l.append(new core::egg(5, QPoint(7850, 1080)));

    return l;
  }

  const QList<core::block*> level1::lifes(const QList<bool>& already_acquired) const
  {
    QList<core::block*> l;

    if (already_acquired.isEmpty() or not already_acquired.at(0))
      l.append(new core::life(1, QPoint(300, 1600)));

    return l;
  }

  const QList<core::block*> level1::baseground() const
  {
    QList<core::block*> l;

    //block 1
    l.append(new world1::base_ground(QPoint(0, 1750), 200));
    l.append(new world1::base_earth(QPoint(200, 1750), 200));
    l.append(new world1::base_ground(QPoint(200, 1700), 200));
    l.append(new world1::base_ground(QPoint(400, 1750), 400));
    l.append(new world1::base_ground(QPoint(800, 1650), 200));
    l.append(new world1::base_earth(QPoint(800, 1700), 200, 100));
    l.append(new world1::base_ground(QPoint(600, 1525), 150));
    l.append(new world1::base_ground(QPoint(850, 1450), 250));
    l.append(new world1::base_earth(QPoint(1000, 1550), 100, 250));

    //block 2
    l.append(new world1::base_ground(QPoint(1100, 1350), 200));
    l.append(new world1::base_earth(QPoint(1100, 1400), 200, 100));
    l.append(new world1::base_earth(QPoint(1100, 1550), 200, 250));
    l.append(new world1::base_ground(QPoint(1300, 1250), 200));
    l.append(new world1::base_earth(QPoint(1300, 1300), 200, 200));
    l.append(new world1::base_earth(QPoint(1300, 1550), 200, 250));
    l.append(new world1::base_ground(QPoint(1600, 1250), 100));
    l.append(new world1::base_ground(QPoint(1800, 1250), 100));
    l.append(new world1::base_ground(QPoint(2000, 1250), 100));
    l.append(new world1::base_ground(QPoint(1500, 1750), 300));
    l.append(new world1::base_ground(QPoint(1800, 1700), 100));
    l.append(new world1::base_earth(QPoint(1800, 1750), 100));
    l.append(new world1::base_ground(QPoint(1900, 1750), 300));
    l.append(new world1::base_ground(QPoint(2200, 1000), 200));
    l.append(new world1::base_earth(QPoint(2200, 1050), 200, 100));
    l.append(new world1::base_earth(QPoint(2200, 1250), 200, 400));
    l.append(new world1::base_earth(QPoint(2200, 1750), 200));

    //block 3
    l.append(new world1::base_ground(QPoint(2400, 1250), 400));
    l.append(new world1::base_ground(QPoint(3000, 1250), 400));
    l.append(new world1::base_ground(QPoint(3600, 1250), 400));
    l.append(new world1::base_ground(QPoint(2400, 1750), 200));
    l.append(new world1::base_ground(QPoint(2600, 1700), 200));
    l.append(new world1::base_ground(QPoint(2800, 1650), 200));
    l.append(new world1::base_ground(QPoint(3000, 1600), 200));
    l.append(new world1::base_ground(QPoint(3200, 1550), 200));
    l.append(new world1::base_ground(QPoint(3400, 1500), 200));
    l.append(new world1::base_ground(QPoint(3600, 1450), 200));
    l.append(new world1::base_ground(QPoint(3800, 1400), 400));
    l.append(new world1::base_earth(QPoint(2600, 1750), 200));
    l.append(new world1::base_earth(QPoint(2800, 1700), 200, 100));
    l.append(new world1::base_earth(QPoint(3000, 1650), 200, 150));
    l.append(new world1::base_earth(QPoint(3200, 1600), 200, 200));
    l.append(new world1::base_earth(QPoint(3400, 1550), 200, 250));
    l.append(new world1::base_earth(QPoint(3600, 1500), 200, 300));
    l.append(new world1::base_earth(QPoint(3800, 1450), 400, 350));

    //block 4
    l.append(new world1::base_ground(QPoint(4300, 1400), 200));
    l.append(new world1::base_ground(QPoint(4600, 1400), 200));
    l.append(new world1::base_ground(QPoint(4900, 1400), 200));
    l.append(new world1::base_ground(QPoint(5200, 1400), 200));
    l.append(new world1::base_ground(QPoint(4200, 1750), 1800));
    l.append(new world1::base_earth(QPoint(5200, 1450), 200, 200));

    //block 5
    l.append(new world1::base_ground(QPoint(6000, 1750), 400));
    l.append(new world1::base_ground(QPoint(6500, 1750), 400));

    //block 6
    l.append(new world1::base_ground(QPoint(6900, 1750), 200));
    l.append(new world1::base_ground(QPoint(7100, 1650), 100));
    l.append(new world1::base_earth(QPoint(7100, 1700), 100, 100));
    l.append(new world1::base_ground(QPoint(7200, 1550), 100));
    l.append(new world1::base_earth(QPoint(7200, 1600), 100, 200));
    l.append(new world1::base_ground(QPoint(7300, 1450), 100));
    l.append(new world1::base_earth(QPoint(7300, 1500), 100, 300));
    l.append(new world1::base_ground(QPoint(7400, 1350), 100));
    l.append(new world1::base_earth(QPoint(7400, 1400), 100, 400));
    l.append(new world1::base_ground(QPoint(7500, 1300), 100));
    l.append(new world1::base_earth(QPoint(7500, 1350), 100, 450));
    l.append(new world1::base_ground(QPoint(7600, 1200), 100));
    l.append(new world1::base_earth(QPoint(7600, 1250), 100, 550));
    l.append(new world1::base_ground(QPoint(7700, 1150), 100));
    l.append(new world1::base_earth(QPoint(7700, 1200), 100, 600));
    l.append(new world1::base_ground(QPoint(7800, 1100), 100));
    l.append(new world1::base_earth(QPoint(7800, 1150), 100, 650));
    l.append(new world1::base_ground(QPoint(7900, 800), 100));
    l.append(new world1::base_earth(QPoint(7900, 850), 100, 950));

    return l;
  }

  const QList<core::block*> level1::foreground() const
  {
    QList<core::block*> l;

    //block 1 / 2
    l.append(new world1::fore_earth(QPoint(1000, 1500), 450));

    //block 2
    l.append(new world1::fore_earth(QPoint(2200, 1650), 200, 100));
    l.append(new world1::fore_earth(QPoint(2200, 1150), 200, 100));

    //block 4
    l.append(new world1::fore_ground(QPoint(4200, 1400), 100));
    l.append(new world1::fore_ground(QPoint(4500, 1400), 100));
    l.append(new world1::fore_ground(QPoint(4800, 1400), 100));
    l.append(new world1::fore_ground(QPoint(5100, 1400), 100));
    l.append(new world1::fore_earth(QPoint(4200, 1450), 1000, 200));

    return l;
  }

  const QList<core::block*> level1::death_items() const
  {
    QList<core::block*> l;

    //block 5
    l.append(new world1::death_chocolate(QPoint(6400, 1750), 100));

    return l;
  }

} // namespace world1
