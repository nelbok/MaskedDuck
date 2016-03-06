#include <QMouseEvent>
#include <QGraphicsItem>

//FIXME
#include "../game/constant.hpp"

#include "editor/scene/scene_world.hpp"
#include "editor/widget/tools/edit_connexion.hpp"
#include "editor/widget/tools/edit_stage.hpp"
#include "editor/widget/body/body_world_view.hpp"

Q_DECLARE_METATYPE(world_item_ptr)

namespace editor
{

  namespace widget
  {

    body_world_view::body_world_view(editor_world_ptr w, QWidget* parent)
      : QGraphicsView(parent)
      , scene_(new scene::world(w))
      , world_(w)
      , previous_pos_(QPoint(0, 0))
      , current_(0)
      , current_action_(widget::body_world_view::SIZE)
    {
      setFixedSize(AMD_SCENE_WIDTH + 2, AMD_SCENE_HEIGHT + 2);
      setScene(scene_);
      setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }


    widget::body_world_view::action_type body_world_view::current_action() const
    {
      return current_action_;
    }

    void body_world_view::current_action(widget::body_world_view::action_type ca)
    {
      current_action_ = ca;
    }


    void body_world_view::mousePressEvent(QMouseEvent* e)
    {
      QGraphicsView::mousePressEvent(e);
      // Save the previous position of the mouse.
      previous_pos_ = mapToScene(e->pos()).toPoint();
      // Get the world item under the mouse.
      current_ = scene_->itemAt(mapToScene(e->pos()), QTransform());
    }

    void body_world_view::mouseReleaseEvent(QMouseEvent* e)
    {
      QGraphicsView::mouseReleaseEvent(e);
      // Get the delta between the previous position and the current position of the mouse.
      QPoint delta = mapToScene(e->pos()).toPoint() - previous_pos_;
      switch (current_action_)
      {
        case MOVE:
          // If the delta is not null, move the world item or the background of the world.
          if (not delta.isNull())
          {
            if (world_item_ptr item = current_->data(Qt::UserRole).value<world_item_ptr>())
              world_->modify_world_item(item, item->pos() + delta);
            else
              world_->pos(world_->pos() + delta);
          }
          break;
        case EDIT:
          // If the delta is null, edit the world item or the connexion under the mouse.
          if (delta.isNull())
          {
            if (world_item_ptr item = current_->data(Qt::UserRole).value<world_item_ptr>())
            {
              if (item->is_stage())
                (new tools::edit_stage(world_, item, this))->show();
            }
            else
            {
              if (world_item_ptr w1 = current_->data(Qt::UserRole + 1).value<world_item_ptr>())
                if (world_item_ptr w2 = current_->data(Qt::UserRole + 2).value<world_item_ptr>())
                  (new tools::edit_connexion(world_, w1, w2, this))->show();
            }
          }
          break;
        case ROAD:
          // Test if it possible to create a connexion between two different world item.
          if (not delta.isNull())
          {
            if (world_item_ptr w1 = current_->data(Qt::UserRole).value<world_item_ptr>())
              if (world_item_ptr w2 = scene_->itemAt(mapToScene(e->pos()), QTransform())->data(Qt::UserRole).value<world_item_ptr>())
                (new tools::edit_connexion(world_, w1, w2, this))->show();
          }
          break;
        case REMOVE:
          // If the delta is null, remove a world item or a connexion under the mouse.
          if (delta.isNull())
          {
            if (world_item_ptr item = current_->data(Qt::UserRole).value<world_item_ptr>())
            {
              if (world_->return_item() != item)
                world_->remove_world_item(item);
            }
            else
            {
              if (world_item_ptr w1 = current_->data(Qt::UserRole + 1).value<world_item_ptr>())
                if (world_item_ptr w2 = current_->data(Qt::UserRole + 2).value<world_item_ptr>())
                  world_->remove_world_item_connexion(w1, w2);
            }
          }
          break;
        case ADD_POINT:
          // Verify if it possible to add a point.
          if (delta.isNull() and current_->data(Qt::UserRole).isNull())
          {
            world_->add_world_item(previous_pos_);
          }
          break;
        case ADD_LEVEL:
          // Verify if it possible to add a level.
          if (delta.isNull() and current_->data(Qt::UserRole).isNull())
          {
            (new tools::edit_stage(world_, core::world_item::LEVEL, previous_pos_, this))->show();
          }
          break;
        case SIZE:
          break;
      }
    }

  } // namespace widget

} // namespace editor
