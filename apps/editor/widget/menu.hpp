#ifndef EDITOR_WIDGET_MENU_HPP
# define EDITOR_WIDGET_MENU_HPP

# include <QMenuBar>

# include "editor/data/world.hpp"

namespace editor
{

  namespace widget
  {

    /*!
     *  Main menu of the editor.
     */

    class menu : public QMenuBar
    {
      Q_OBJECT

      public:
        menu(editor_world_ptr w, QWidget* parent = 0);

      private:
        void init();

        editor_world_ptr world_;

      private slots:
        void do_edit();
        void do_save();
        void do_load();
        void do_generate();

    };

  } // namespace widget

} // namespace editor

#endif // EDITOR_WIDGET_MENU_HPP
