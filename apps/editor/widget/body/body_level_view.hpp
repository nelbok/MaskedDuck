#ifndef EDITOR_WIDGET_BODY_LEVEL_VIEW_HPP
# define EDITOR_WIDGET_BODY_LEVEL_VIEW_HPP

# include <QGraphicsView>

# include "editor/data/stage/level.hpp"
# include "editor/data/world.hpp"

namespace graphics_engine
{
  class scene_level;
}

namespace editor
{

  namespace widget
  {

    /*!
     *  Graphics view for a level.\n
     *  Show a level and manage the action on it.
     */

    class body_level_view : public QGraphicsView
    {
      Q_OBJECT

      public:
        enum action_type
        {
          ADD,
          REMOVE,

          SIZE
        };

        body_level_view(editor_world_ptr w, editor_level_ptr l, QWidget* parent = 0);

        // Manage current action on the view
        widget::body_level_view::action_type current_action() const;
        void current_action(widget::body_level_view::action_type);

        // Manage current resource on the view
        void reset_res_add();
        void res_add(const data::item& res);

      protected:
        virtual void mousePressEvent(QMouseEvent*);
        virtual void mouseReleaseEvent(QMouseEvent*);
        virtual void scrollContentsBy(int dx, int dy);

      private:
        graphics_engine::scene_level* scene_;
        editor_world_ptr world_;
        editor_level_ptr level_;
        QPoint previous_pos_;
        QGraphicsItem* current_;
        widget::body_level_view::action_type current_action_;
        data::item res_add_;

        // Methods to calculate the rect drawing by the user.
        const QRect create_rect(const QPoint& pos1, const QPoint& pos2) const;
        void clean(int& offset1, int& offset2) const;
        void clean(int& a) const;

      private slots:
        void do_reload();
    };

  } // namespace widget

} // namespace editor

#endif // EDITOR_WIDGET_BODY_LEVEL_VIEW_HPP
