#ifndef EDITOR_WIDGET_BODY_LEVEL_HPP
# define EDITOR_WIDGET_BODY_LEVEL_HPP

# include <QWidget>

# include "editor/data/stage/level.hpp"
# include "editor/data/world.hpp"

class QPushButton;
class QGridLayout;

namespace editor
{

  namespace widget
  {
    class body_level_view;

    /*!
     *  Work space for the world.\n
     *  Show the different possible actions.
     */

    class body_level : public QWidget
    {
      Q_OBJECT

      public:
        body_level(editor_world_ptr w, editor_level_ptr l, QWidget* parent = 0);

      private:
        editor_world_ptr world_;
        editor_level_ptr level_;
        QList<QPushButton*> btn_level_;
        widget::body_level_view* view_;
        QPushButton* btn_add_;

        void init();
        void update_buttons(QObject* current);
        QPushButton* add_button(QGridLayout* l, const QString& name, int column, const char* slot, const QString& = QString(""));

      private slots:
        void do_add_pushed();
        void do_reset_add_button();
        void do_update_add_button(int index);
        void do_remove_pushed();
    };

  } // namespace widget

} // namespace editor

#endif // EDITOR_WIDGET_BODY_LEVEL_HPP
