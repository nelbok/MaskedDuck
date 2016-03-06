#include "stage/level1.hpp"
#include "stage/level2.hpp"
#include "stage/level3.hpp"
#include "stage/level4.hpp"
#include "stage/level5.hpp"
#include "world1.hpp"

namespace world1
{

  world1::world1()
  {
    world_item_ptr wi1 = world_item_ptr(new core::world_item(QPoint(250, 250), true));
    add_world_item(wi1);

    level_ptr l1 = level_ptr(new ::world1::level1);
    world_item_ptr wi2 = world_item_ptr(new core::world_item(QPoint(300, 250), l1));
    core::world_item::add_connexion(wi1, wi2);
    add_world_item(wi2);

    world_item_ptr wi3 = world_item_ptr(new core::world_item(QPoint(300, 300)));
    core::world_item::add_connexion(wi2, wi3, 1);
    add_world_item(wi3);

    level_ptr l2 = level_ptr(new ::world1::level2);
    world_item_ptr wi4 = world_item_ptr(new core::world_item(QPoint(350, 300), l2));
    core::world_item::add_connexion(wi3, wi4);
    add_world_item(wi4);

    world_item_ptr wi5 = world_item_ptr(new core::world_item(QPoint(400, 300)));
    core::world_item::add_connexion(wi4, wi5, 1);
    add_world_item(wi5);

    level_ptr l3 = level_ptr(new ::world1::level3);
    world_item_ptr wi6 = world_item_ptr(new core::world_item(QPoint(450, 300), l3));
    core::world_item::add_connexion(wi5, wi6);
    add_world_item(wi6);

    world_item_ptr wi7 = world_item_ptr(new core::world_item(QPoint(350, 350)));
    core::world_item::add_connexion(wi4, wi7, 2);
    add_world_item(wi7);

    level_ptr l4 = level_ptr(new ::world1::level4);
    world_item_ptr wi8 = world_item_ptr(new core::world_item(QPoint(400, 350), l4));
    core::world_item::add_connexion(wi7, wi8);
    add_world_item(wi8);

    world_item_ptr wi9 = world_item_ptr(new core::world_item(QPoint(450, 350)));
    core::world_item::add_connexion(wi8, wi9, 1);
    core::world_item::add_connexion(wi6, wi9, 1);
    add_world_item(wi9);

    level_ptr l5 = level_ptr(new ::world1::level5);
    world_item_ptr wi10 = world_item_ptr(new core::world_item(QPoint(500, 350), l5));
    core::world_item::add_connexion(wi9, wi10);
    add_world_item(wi10);
  }


  int world1::id() const
  {
    return 1;
  }

  const QString world1::name() const
  {
    return "The forest of ducks";
  }

  const QPixmap world1::pixmap() const
  {
    return QPixmap(":/world1/world.png");
  }

  const QPoint world1::pos() const
  {
    return QPoint(215, 210);
  }

  const QPoint world1::global_pos() const
  {
    return QPoint(800, 500);
  }

} // namespace world1
