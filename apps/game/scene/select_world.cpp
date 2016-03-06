#include <QKeyEvent>

#include "game/items/info_item.hpp"
#include "game/items/menu_item.hpp"
#include "game/items/status_world.hpp"
#include "game/scene/select_world.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace scene
  {

    select_world::select_world(game_player_ptr p)
      : player_(p)
      , map_(p->map())
      , info_item_(0)
      , menuitem_(0)
      , statusworld_(0)
      , menu_(false)
    {
      load();
    }


    void select_world::keyPressEvent(QKeyEvent* e)
    {
      if (e->isAutoRepeat())
        return;

      switch (e->key())
      {
        case Qt::Key_Left:
        {
          if (menu_)
            break;

          QGraphicsItem* ci = worlds_.key(player_->current_world());
          QMap<QGraphicsItem*, world_ptr>::iterator i = worlds_.find(ci);
          if (i == worlds_.begin())
            i = --worlds_.end();
          else
            --i;
          player_->current_world(i.value());
          update_selection();
          break;
        }
        case Qt::Key_Right:
        {
          if (menu_)
            break;

          QGraphicsItem* ci = worlds_.key(player_->current_world());
          QMap<QGraphicsItem*, world_ptr>::iterator i = worlds_.find(ci);
          if (i == --worlds_.end())
            i = worlds_.begin();
          else
            ++i;
          player_->current_world(i.value());
          update_selection();
          break;
        }
        case Qt::Key_Up:
        {
          if (not menu_)
            break;
          menuitem_->move_to_up();
          break;
        }
        case Qt::Key_Down:
        {
          if (not menu_)
            break;
          menuitem_->move_to_down();
          break;
        }
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
              break;
            }
            if (t == items::menu_item::QUIT_GAME)
              emit sig_quit_game_selected();
          }
          // Choose a world if the menu is not active
          else
          {
            emit sig_world_selected();
          }
          break;
        }
        default:
          QGraphicsScene::keyPressEvent(e);
      }
    }


    void select_world::load()
    {
      clear();
      setSceneRect(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);
      worlds_.clear();

      // Draw scene
      draw_background(AMD_BACK_DEPTH);
      draw_baseground(AMD_BASE_DEPTH);
      draw_info(AMD_INFO_DEPTH);
      draw_status_world(AMD_INFO_DEPTH);

      // Default world
      world_ptr w = player_->current_world();
      if (not w)
        player_->current_world(map_->worlds().at(0));

      update_selection();
    }

    void select_world::draw_background(int depth)
    {
      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(QColor("#7b4524"));
      QGraphicsRectItem* r = new QGraphicsRectItem(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);
      r->setZValue(depth);
      r->setBrush(brush);
      addItem(r);
    }

    void select_world::draw_baseground(int depth)
    {
      QGraphicsItemGroup* group = new QGraphicsItemGroup();
      group->setPos(0, 0);
      group->setZValue(depth);
      addItem(group);

      QList<world_ptr> ws = map_->worlds();
      for (int i = 0; i < ws.size(); ++i)
      {
        world_ptr w = ws.at(i);
        QGraphicsPixmapItem* pix = new QGraphicsPixmapItem(w->pixmap());
        pix->setPos(w->global_pos() * AMD_SW_FACTOR);
        pix->setZValue(depth);
        pix->setScale(AMD_SW_FACTOR);
        group->addToGroup(pix);
        worlds_.insert(pix, w);
      }
    }

    void select_world::draw_menu(int depth)
    {
      menuitem_ = new items::menu_item(items::menu_item::SELECT_WORLD);
      menuitem_->setPos(AMD_SCENE_WIDTH / 2, AMD_SCENE_HEIGHT / 2);
      menuitem_->setZValue(depth);
      addItem(menuitem_);
    }

    void select_world::draw_info(int depth)
    {
      info_item_ = new items::info_item(player_);
      info_item_->setPos(0, 0);
      info_item_->setZValue(depth);
      addItem(info_item_);
    }

    void select_world::draw_status_world(int depth)
    {
      statusworld_ = new items::status_world(player_);
      statusworld_->setPos(AMD_SCENE_WIDTH / 2, 80);
      statusworld_->setZValue(depth);
      addItem(statusworld_);
    }


    void select_world::update_selection()
    {
      info_item_->update_text();
      statusworld_->update_text();
      world_ptr w = player_->current_world();

      QMapIterator<QGraphicsItem*, world_ptr> i(worlds_);
      while (i.hasNext())
      {
        i.next();
        QGraphicsItem* item = i.key();
        world_ptr world = i.value();

        item->setPos(world->global_pos() * AMD_SW_FACTOR);
        item->setZValue(AMD_BASE_DEPTH);
        if (world == w)
        {
          item->setY(item->y() - 15);
          item->setZValue(AMD_FORE_DEPTH);
        }
      }
    }

  } // namespace scene

} // namespace game
