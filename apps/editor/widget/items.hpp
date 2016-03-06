#ifndef EDITOR_WIDGET_ITEMS_HPP
# define EDITOR_WIDGET_ITEMS_HPP

# include <QFrame>

# include "editor/data/resource.hpp"

class QTableWidget;

namespace editor
{

  namespace widget
  {

    /*!
     *  Items of the editor.\n
     *  Show the items of the resource
     */

    class items : public QFrame
    {
      Q_OBJECT

      public:
        items(editor_resource_ptr res, QWidget* parent = 0);

      private:
        editor_resource_ptr resource_;

        QTableWidget* data_;

      private slots:
        void do_update();

        void do_edit();
        void do_add();
        void do_remove();
        void do_generate();
    };

  } // namespace widget

} // namespace editor

#endif // EDITOR_WIDGET_ITEMS_HPP
