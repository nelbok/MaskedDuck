#include <QKeyEvent>

#include "graphics_engine/constant.hpp"

#include "game/items/duck.hpp"
#include "game/items/info_item.hpp"
#include "game/items/lose_item.hpp"
#include "game/items/win_item.hpp"
#include "game/items/menu_item.hpp"
#include "game/scene/scene_level.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace scene
  {

    level::level(game_player_ptr p)
      : player_(p)
      , duck_(0)
      , duck_collide_(0)
      , infoitem_(0)
      , menuitem_(0)
      , left_pushed_(false)
      , right_pushed_(false)
      , space_pushed_(false)
      , jump_(0)
      , lose_(false)
      , win_(false)
      , menu_(false)
      , timer_id_(0)
      , acquired_life_(false)
    {
      load();
    }

    level::~level()
    {
      if (duck_collide_)
        delete duck_collide_;
    }


    void level::keyPressEvent(QKeyEvent* e)
    {
      if (e->isAutoRepeat())
        return;

      switch (e->key())
      {
        case Qt::Key_Left:
          // Go to the left if the menu is not active.
          if (not menu_) left_pushed_ = true;
          break;
        case Qt::Key_Right:
          // Go to the right if the menu is not active.
          if (not menu_) right_pushed_ = true;
          break;
        case Qt::Key_Space:
          // Jump if the menu is not active.
          if (not menu_) space_pushed_ = true;
          break;
        case Qt::Key_Up:
        {
          // Draw win widget of an opening of a door.
          if (not win_ and collide_with_door())
          {
            draw_win(AMD_INFO_DEPTH);
            kill_timer();
            win_ = true;
          }
          // Go back up the selection if the menu is active.
          if (menu_)
          {
            menuitem_->move_to_up();
          }
          break;
        }
        case Qt::Key_Down:
        {
          // Goes down the selection if the menu is active.
          if (menu_)
          {
            menuitem_->move_to_down();
          }
          break;
        }
        case Qt::Key_Escape:
        {
          // Show or hide the menu if the player does not have either to win or to lose.
          if (not lose_ and not win_)
          {
            if (menu_)
            {
              if (menuitem_)
              {
                delete menuitem_;
                menuitem_ = 0;
              }

              start_timer();
              menu_ = false;
            }
            else
            {
              draw_menu(AMD_INFO_DEPTH);
              kill_timer();
              menu_ = true;
            }
          }
          break;
        }
        case Qt::Key_Return:
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

              start_timer();
              menu_ = false;
              break;
            }
            if (t == items::menu_item::QUIT_LEVEL)
              emit sig_player_lose();
            if (t == items::menu_item::QUIT_GAME)
              emit sig_quit_game_selected();
            break;
          }
          if (lose_)
            emit sig_player_lose();
          if (win_)
            emit sig_player_win(collide_with_door()->data(Qt::UserRole).toInt(), acquired_eggs_);
          break;
        default:
          QGraphicsScene::keyPressEvent(e);
      }
    }

    void level::keyReleaseEvent(QKeyEvent* e)
    {
      if (e->isAutoRepeat())
        return;

      switch (e->key())
      {
        case Qt::Key_Left:
          left_pushed_ = false;
          break;
        case Qt::Key_Right:
          right_pushed_ = false;
          break;
        case Qt::Key_Space:
          space_pushed_ = false;
          break;
        default:
          QGraphicsScene::keyReleaseEvent(e);
      }
    }

    void level::timerEvent(QTimerEvent*)
    {
      // Manage the movement
      if (left_pushed_ and not right_pushed_ and can_move_to_left())
        move_to_left();
      if (not left_pushed_ and right_pushed_ and can_move_to_right())
        move_to_right();
      if (not jump_ and can_move_to_bottom())
        move_to_bottom();

      // Manage the jump
      if (not jump_ and space_pushed_ and not can_move_to_bottom())
        jump_ = 50;
      if (jump_)
      {
        jump_--;
        for (int i = 0; i < 3; ++i)
        {
          if (can_move_to_top())
            move_to_top();
          else
            jump_ = 0;
        }
      }

      // Manage the death of the player.
      if (duck_->y() > AMD_MAP_HEIGHT or collide_with_death_items())
      {
        kill_timer();
        lose_ = true;
        draw_lose(AMD_INFO_DEPTH);
      }

      // Manage the obtaining of an life.
      if (QGraphicsItem* life = collide_with_life())
      {
        player_->acquired_life(life->data(Qt::UserRole).toInt());
        player_->add_life();
        acquired_life_ = true;
        infoitem_->update_text();
        lifeitem_->removeFromGroup(life);
        delete life;
      }

      // Manage the obtaining of an egg.
      if (QGraphicsItem* egg = collide_with_egg())
      {
        acquired_eggs_.append(egg->data(Qt::UserRole).toInt());
        eggsitem_->removeFromGroup(egg);
        delete egg;
      }
    }


    void level::load()
    {
      level_ptr l = player_->current_world_item()->level();

      reload(l, player_->acquired_eggs(), player_->acquired_lifes());

      kill_timer();

      // FIXME: Test me ~
      left_pushed_ = false;
      right_pushed_ = false;
      space_pushed_ = false;
      jump_ = 0;

      // Get start position
      QPoint sp = l->start_position();
      duck_ = new items::duck();
      duck_->setPos(sp);
      duck_->setZValue(0);
      addItem(duck_);
      duck_collide_ = new items::duck();

      // Draw info
      draw_info(AMD_INFO_DEPTH);

      // Scene position
      int x_scene = sp.x() - AMD_SCENE_WIDTH / 2;
      int y_scene = sp.y() - AMD_SCENE_HEIGHT / 2;
      if (x_scene < 0)                                  x_scene = 0;
      if (y_scene < 0)                                  y_scene = 0;
      if (x_scene > AMD_MAP_WIDTH - AMD_SCENE_WIDTH)    x_scene = AMD_MAP_WIDTH - AMD_SCENE_WIDTH;
      if (y_scene > AMD_MAP_HEIGHT - AMD_SCENE_HEIGHT)  y_scene = AMD_MAP_HEIGHT - AMD_SCENE_HEIGHT;
      move_scene(x_scene, y_scene);

      start_timer();
    }

    void level::kill_timer()
    {
      if (timer_id_)
        killTimer(timer_id_);
      timer_id_ = 0;
    }

    void level::start_timer()
    {
      timer_id_ = startTimer(AMD_TIMER);
    }

    void level::draw_menu(int depth)
    {
      menuitem_ = new items::menu_item(items::menu_item::SCENE_LEVEL);
      menuitem_->setPos(sceneRect().x() + AMD_SCENE_WIDTH / 2, sceneRect().y() + AMD_SCENE_HEIGHT / 2);
      menuitem_->setZValue(depth);
      addItem(menuitem_);
    }

    void level::draw_info(int depth)
    {
      infoitem_ = new items::info_item(player_);
      infoitem_->setPos(0, 0);
      infoitem_->setZValue(depth);
      addItem(infoitem_);
    }

    void level::draw_lose(int depth)
    {
      items::lose_item* loseitem = new items::lose_item();
      loseitem->setPos(sceneRect().x(), sceneRect().y() + AMD_SCENE_HEIGHT / 2);
      loseitem->setZValue(depth);
      addItem(loseitem);
    }

    void level::draw_win(int depth)
    {
      items::win_item* winitem = new items::win_item(player_, acquired_eggs_, acquired_life_);
      winitem->setPos(sceneRect().x() + AMD_SCENE_WIDTH / 2, sceneRect().y() + AMD_SCENE_HEIGHT / 2);
      winitem->setZValue(depth);
      addItem(winitem);
    }


    bool level::can_move_to_left()
    {
      return duck_->x() > 5 and not collide_with_obstacles(-AMD_DELTA, 0);
    }

    bool level::can_move_to_right()
    {
      return duck_->x() < AMD_MAP_WIDTH - duck_->boundingRect().width() and not collide_with_obstacles(AMD_DELTA, 0);
    }

    bool level::can_move_to_bottom()
    {
      return not collide_with_obstacles(0, AMD_DELTA);
    }

    bool level::can_move_to_top()
    {
      return not collide_with_obstacles(0, -AMD_DELTA);
    }

    void level::move_to_left()
    {
      QRectF r = sceneRect();
      if (r.x() > 0 and duck_->x() + 15 == r.x() + AMD_SCENE_WIDTH / 2)
        move_scene(-AMD_DELTA, 0);
      duck_->setX(duck_->x() - AMD_DELTA);
      duck_->go_to_left();
    }

    void level::move_to_right()
    {
      QRectF r = sceneRect();
      if (r.x() < AMD_MAP_WIDTH - AMD_SCENE_WIDTH and duck_->x() + 15 == r.x() + AMD_SCENE_WIDTH / 2)
        move_scene(AMD_DELTA, 0);
      duck_->setX(duck_->x() + AMD_DELTA);
      duck_->go_to_right();
    }

    void level::move_to_bottom()
    {
      QRectF r = sceneRect();
      if (r.y() < AMD_MAP_HEIGHT - AMD_SCENE_HEIGHT and duck_->y() + 15 == r.y() + AMD_SCENE_HEIGHT / 2)
        move_scene(0, AMD_DELTA);
      duck_->setY(duck_->y() + AMD_DELTA);
    }

    void level::move_to_top()
    {
      QRectF r = sceneRect();
      if (r.y() > 0 and duck_->y() + 15 == r.y() + AMD_SCENE_HEIGHT / 2)
        move_scene(0, -AMD_DELTA);
      duck_->setY(duck_->y() - AMD_DELTA);
    }

    void level::move_scene(qreal dx, qreal dy)
    {
      QRectF r = sceneRect();
      r.translate(dx, dy);
      setSceneRect(r);

      infoitem_->setPos(r.topLeft());
      move_background(r.topLeft());
    }

    bool level::collide_with_obstacles(qreal dx, qreal dy)
    {
      duck_collide_->setX(duck_->x() + dx);
      duck_collide_->setY(duck_->y() + dy);

      return collide(duck_collide_, baseitem_->childItems());
    }

    bool level::collide_with_death_items() const
    {
      return collide(duck_, deaditem_->childItems());
    }

    QGraphicsItem* level::collide_with_door() const
    {
      return collide(duck_, dooritem_->childItems());
    }

    QGraphicsItem* level::collide_with_life() const
    {
      return collide(duck_, lifeitem_->childItems());
    }

    QGraphicsItem* level::collide_with_egg() const
    {
      return collide(duck_, eggsitem_->childItems());
    }

    QGraphicsItem* level::collide(QGraphicsItem* obj, const QList<QGraphicsItem*>& list) const
    {
      for (int i = 0; i < list.size(); ++i)
      {
        if (list.at(i)->collidesWithItem(obj))
          return list.at(i);
      }

      return 0;
    }

  } // namespace scene

} // namespace game
