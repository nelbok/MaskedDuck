#ifndef EDITOR_WIDGET_BODY_WORLD_HPP
# define EDITOR_WIDGET_BODY_WORLD_HPP

# include <QWidget>

# include "editor/data/world.hpp"

class QPushButton;
class QGridLayout;

namespace editor
{

  namespace widget
  {
    class body_world_view;

    /*!
     *  Work space for the world.\n
     *  Show the different possible actions.
     */

    class body_world : public QWidget
    {
      Q_OBJECT

      public:
        body_world(editor_world_ptr w, QWidget* parent = 0);

      private:
        editor_world_ptr world_;
        QList<QPushButton*> btn_world_;
        widget::body_world_view* view_;

        void init();
        void update_buttons(QObject* current);
        QPushButton* add_button(QGridLayout* l, const QString& name, int column, const char* slot, const QString& = QString(""));

      private slots:
        void do_move_pushed();
        void do_edit_pushed();
        void do_road_pushed();
        void do_remove_pushed();
        void do_add_point_pushed();
        void do_add_level_pushed();
    };

  } // namespace widget

} // namespace editor

#endif // EDITOR_WIDGET_BODY_WORLD_HPP
