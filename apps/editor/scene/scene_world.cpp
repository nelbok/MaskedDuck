#include <QGraphicsItem>

//FIXME
#include "../game/constant.hpp"

#include "editor/items/road.hpp"
#include "editor/items/world_item.hpp"
#include "editor/scene/scene_world.hpp"

namespace editor
{

  namespace scene
  {

    world::world(editor_world_ptr w)
      : world_(w)
    {
      connect(world_.data(), SIGNAL(sig_world_updated()), SLOT(do_reload()));
      do_reload();
    }


    void world::do_reload()
    {
      clear();
      setSceneRect(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);

      // Draw scene
      draw_background(AMD_BACK_DEPTH);
      draw_baseground(AMD_BASE_DEPTH);
    }


    void world::draw_background(int depth)
    {
      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(QColor("#7b4524"));
      QGraphicsRectItem* r = new QGraphicsRectItem(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);
      r->setZValue(depth);
      r->setBrush(brush);
      addItem(r);

      QGraphicsPixmapItem* pix = new QGraphicsPixmapItem(world_->pixmap());
      pix->setPos(world_->pos());
      pix->setZValue(depth);
      addItem(pix);
    }

    void world::draw_baseground(int depth)
    {
      QGraphicsItemGroup* group = new QGraphicsItemGroup();
      group->setPos(0, 0);
      group->setZValue(depth);
      addItem(group);

      const QList<world_item_ptr>& list = world_->world_items();

      // Draw connexions
      QList<world_item_ptr> already_draw;
      for (int i = 0; i < list.size(); ++i)
      {
        world_item_ptr w1 = list.at(i);
        QMapIterator<world_item_ptr, int> j(w1->connexions());
        while (j.hasNext())
        {
          j.next();
          world_item_ptr w2 = j.key();
          if (not already_draw.contains(w2))
          {
            int id_door = j.value();
            draw_road(group, w1, w2, id_door);
          }
        }
        already_draw.append(w1);
      }

      // Draw world_items
      for (int i = 0; i < list.size(); ++i)
        draw_world_item(group, list.at(i));
    }


    void world::draw_road(QGraphicsItemGroup* group, world_item_ptr w1, world_item_ptr w2, int id_door)
    {
      // Draw line
      QLineF line(w1->pos(), w2->pos());
      items::road* item = new items::road(w1, w2, id_door, line.length());
      item->setRotation(-line.angle());
      item->setPos(line.p1());
      group->addToGroup(item);
    }


    void world::draw_world_item(QGraphicsItemGroup* group, world_item_ptr data)
    {
      items::world_item* wi = new items::world_item(data);
      wi->setPos(data->pos());
      group->addToGroup(wi);
    }
  } // namespace scene

} // namespace editor
