#include <QMouseEvent>
#include <QGraphicsItem>

//FIXME
#include "../game/constant.hpp"

#include "graphics_engine/scene/scene_level.hpp"

#include "editor/widget/body/body_level_view.hpp"

namespace editor
{

  namespace widget
  {

    body_level_view::body_level_view(editor_world_ptr w, editor_level_ptr l, QWidget* parent)
      : QGraphicsView(parent)
      , scene_(new graphics_engine::scene_level())
      , world_(w)
      , level_(l)
      , previous_pos_(QPoint(0, 0))
      , current_(0)
      , current_action_(widget::body_level_view::SIZE)
    {
      setFixedSize(AMD_SCENE_WIDTH + 2, AMD_SCENE_HEIGHT + 2);
      setScene(scene_);
      setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
      setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

      connect(level_.data(), SIGNAL(sig_level_updated()), SLOT(do_reload()));
      do_reload();
    }


    widget::body_level_view::action_type body_level_view::current_action() const
    {
      return current_action_;
    }

    void body_level_view::current_action(widget::body_level_view::action_type ca)
    {
      current_action_ = ca;
    }


    void body_level_view::reset_res_add()
    {
      res_add_ = data::item();
    }

    void body_level_view::res_add(const data::item& res)
    {
      res_add_ = res;
    }


    void body_level_view::mousePressEvent(QMouseEvent* e)
    {
      QGraphicsView::mousePressEvent(e);
      previous_pos_ = mapToScene(e->pos()).toPoint();
      current_ = scene_->itemAt(mapToScene(e->pos()), QTransform());
    }

    void body_level_view::mouseReleaseEvent(QMouseEvent* e)
    {
      QGraphicsView::mouseReleaseEvent(e);
      QPoint current_pos = mapToScene(e->pos()).toPoint();

      // In work...
      // Missing comments
      switch (current_action_)
      {
        case ADD:
          {
            if (res_add_.id_ >= 0)
              level_->add_item(res_add_, create_rect(previous_pos_, current_pos));
          }
          break;
        case REMOVE:
          {
            //FIXME: Dynamic resource
            level_->remove_item(data::BASEGROUND, create_rect(previous_pos_, current_pos));
          }
          break;
        case SIZE:
          break;
      }
    }

    void body_level_view::scrollContentsBy(int dx, int dy)
    {
      QGraphicsView::scrollContentsBy(dx, dy);
      scene_->move_background(-dx, -dy);
    }


    const QRect body_level_view::create_rect(const QPoint& pos1, const QPoint& pos2) const
    {
      int x1 = pos1.x();
      int y1 = pos1.y();
      int x2 = pos2.x();
      int y2 = pos2.y();

      clean(x1, x2);
      clean(y1, y2);

      return QRect(QPoint(x1, y1), QPoint(x2-1, y2-1));
    }

    void body_level_view::clean(int& offset1, int& offset2) const
    {
      if (offset1 > offset2)
      {
        int tmp = offset1;
        offset1 = offset2;
        offset2 = tmp;
      }

      offset2 += 50;

      clean(offset1);
      clean(offset2);
    }

    void body_level_view::clean(int& a) const
    {
      a = a / 50 * 50;
    }


    void body_level_view::do_reload()
    {
      scene_->reload(level_, QList<bool>(), QList<bool>());
      //FIXME
      scene_->setSceneRect(0, 0, AMD_MAP_WIDTH, AMD_MAP_HEIGHT);
    }

  } // namespace widget

} // namespace editor
