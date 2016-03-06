#ifndef EDITOR_WIDGET_BODY_WORLD_VIEW_HPP
# define EDITOR_WIDGET_BODY_WORLD_VIEW_HPP

# include <QGraphicsView>

# include "editor/data/world.hpp"

namespace editor
{

  namespace scene
  {
    class world;
  }

  namespace widget
  {

    /*!
     *  Graphics view for the world.\n
     *  Show the world and manage the action on it.
     */

    class body_world_view : public QGraphicsView
    {
      public:
        enum action_type
        {
          MOVE,
          EDIT,
          ROAD,
          REMOVE,
          ADD_POINT,
          ADD_LEVEL,

          SIZE
        };

        body_world_view(editor_world_ptr w, QWidget* parent = 0);

        // Manage current action on the view
        widget::body_world_view::action_type current_action() const;
        void current_action(widget::body_world_view::action_type);

      protected:
        virtual void mousePressEvent(QMouseEvent*);
        virtual void mouseReleaseEvent(QMouseEvent*);

      private:
        scene::world* scene_;
        editor_world_ptr world_;
        QPoint previous_pos_;
        QGraphicsItem* current_;
        widget::body_world_view::action_type current_action_;
    };

  } // namespace widget

} // namespace editor

#endif // EDITOR_WIDGET_BODY_WORLD_VIEW_HPP
