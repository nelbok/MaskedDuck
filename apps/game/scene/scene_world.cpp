#include <cmath>

#include <QKeyEvent>

#include "game/items/duck.hpp"
#include "game/items/info_item.hpp"
#include "game/items/menu_item.hpp"
#include "game/items/road.hpp"
#include "game/items/status_level.hpp"
#include "game/items/world_item.hpp"
#include "game/scene/scene_world.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace scene
  {

    world::world(game_player_ptr p)
      : player_(p)
      , world_(p->current_world())
      , menuitem_(0)
      , infoitem_(0)
      , statuslevel_(0)
      , menu_(false)
    {
      load();
    }


    void world::keyPressEvent(QKeyEvent* e)
    {
      if (e->isAutoRepeat())
        return;

      switch (e->key())
      {
        case Qt::Key_Up:
          if (menu_)  menuitem_->move_to_up();
          else        move(90);
          break;
        case Qt::Key_Down:
          if (menu_)  menuitem_->move_to_down();
          else        move(270);
          break;
        case Qt::Key_Left:
          if (not menu_) move(180);
          break;
        case Qt::Key_Right:
          if (not menu_) move(0);
          break;
        case Qt::Key_Escape:
        {
          // Show or hide the menu.
          if (menu_)
          {
            if (menuitem_)
            {
              delete menuitem_;
              menuitem_ = 0;
            }

            menu_ = false;
          }
          else
          {
            draw_menu(AMD_INFO_DEPTH);
            menu_ = true;
          }
          break;
        }
        case Qt::Key_Return:
        {
          // Confirm an option of the menu if it is active.
          if (menu_)
          {
            items::menu_item::selection_type t = menuitem_->current_selection();
            if (t == items::menu_item::CONTINUE)
            {
              if (menuitem_)
              {
                delete menuitem_;
                menuitem_ = 0;
              }

              menu_ = false;
            }
            if (t == items::menu_item::RETURN_MAP)
              emit sig_return_selected();
            if (t == items::menu_item::QUIT_GAME)
              emit sig_quit_game_selected();
          }
          // Choose a world item if the menu is not active
          else
          {
            world_item_ptr wi_duck_ = player_->current_world_item();
            if (wi_duck_->type() == core::world_item::RETURN)
              emit sig_return_selected();
            if (wi_duck_->type() == core::world_item::LEVEL)
              emit sig_level_selected();
            break;
          }
          break;
        }
        default:
          QGraphicsScene::keyPressEvent(e);
      }
    }


    void world::load()
    {
      clear();
      setSceneRect(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);

      // Draw scene
      draw_background(AMD_BACK_DEPTH);
      draw_baseground(AMD_BASE_DEPTH);
      draw_info(AMD_INFO_DEPTH);

      // Draw duck
      world_item_ptr wi_duck = player_->current_world_item();
      if (not wi_duck)
      {
        wi_duck = world_->return_item();
        player_->current_world_item(wi_duck);
        infoitem_->update_text();
      }
      duck_ = new items::duck();
      duck_->setPos(wi_duck->pos());
      duck_->setZValue(AMD_BASE_DEPTH);
      addItem(duck_);

      draw_status_level(AMD_INFO_DEPTH);
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

      QList<world_item_ptr> already_draw;
      world_item_ptr current = world_->return_item();
      already_draw.append(current);
      draw_road(group, already_draw, current);
      draw_world_item(group, current);
    }

    void world::draw_menu(int depth)
    {
      menuitem_ = new items::menu_item(items::menu_item::SCENE_WORLD);
      menuitem_->setPos(AMD_SCENE_WIDTH / 2, AMD_SCENE_HEIGHT / 2);
      menuitem_->setZValue(depth);
      addItem(menuitem_);
    }

    void world::draw_info(int depth)
    {
      infoitem_ = new items::info_item(player_);
      infoitem_->setPos(0, 0);
      infoitem_->setZValue(depth);
      addItem(infoitem_);
    }

    void world::draw_status_level(int depth)
    {
      if (statuslevel_)
      {
        removeItem(statuslevel_);
        delete statuslevel_;
        statuslevel_ = 0;
      }

      if (not player_->current_world_item()->is_level())
        return;

      statuslevel_ = new items::status_level(player_);
      statuslevel_->setPos(AMD_SCENE_WIDTH / 2, 80);
      statuslevel_->setZValue(depth);
      addItem(statuslevel_);
    }


    void world::draw_road(QGraphicsItemGroup* group, QList<world_item_ptr>& already_draw, world_item_ptr current)
    {
      // Draw recursively all the roads the player of which opened the door.
      QMapIterator<world_item_ptr, int> i(current->connexions());
      while (i.hasNext())
      {
        i.next();
        world_item_ptr conn = i.key();
        int id_door = i.value();

        if (id_door == 0
         or (current->is_level() and player_->open_door(current->level(), id_door))
         or (conn->is_level() and player_->open_door(conn->level(), id_door)))
        {
          // Draw line
          QLineF line(current->pos(), conn->pos());
          items::road* item = new items::road(line.length());
          item->setRotation(-line.angle());
          item->setPos(line.p1());
          group->addToGroup(item);

          if (not already_draw.contains(conn))
          {
            already_draw.append(conn);
            draw_road(group, already_draw, conn);
          }
          draw_world_item(group, conn);
        }
      }
    }

    void world::draw_world_item(QGraphicsItemGroup* group, world_item_ptr current)
    {
      items::world_item* wi = new items::world_item(current);
      wi->setPos(current->pos());
      group->addToGroup(wi);
    }


    void world::move(int angle)
    {
      // Move the duck according to the angle if the world item exists and if the door is opened.
      world_item_ptr wi_duck = player_->current_world_item();
      QMapIterator<world_item_ptr, int> i(wi_duck->connexions());
      while (i.hasNext())
      {
        i.next();
        world_item_ptr conn = i.key();
        int id_door = i.value();
        bool possible = true;

        if (id_door > 0)
        {
          if (wi_duck->is_level())
            possible = player_->open_door(wi_duck->level(), id_door);
          if (conn->is_level())
            possible = player_->open_door(conn->level(), id_door);
        }

        QLineF line(wi_duck->pos(), conn->pos());
        if (std::floor(line.angle() + .5) == angle and possible)
        {
          wi_duck = conn;
          duck_->setPos(wi_duck->pos());
          player_->current_world_item(wi_duck);
          infoitem_->update_text();
          draw_status_level(AMD_INFO_DEPTH);
          return;
        }
      }
    }

  } // namespace scene

} // namespace game
