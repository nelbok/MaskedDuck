#ifndef EDITOR_TOOLS_SELECT_WORLD_HPP
# define EDITOR_TOOLS_SELECT_WORLD_HPP

# include <QDialog>

# include "editor/data/world.hpp"

class QLineEdit;

namespace editor
{

  namespace tools
  {

    /*!
     *  Select a world.
     */

    class select_world : public QDialog
    {
      Q_OBJECT

      public:
        select_world(editor_world_ptr w, QWidget* parent);

      private:
        editor_world_ptr world_;

        QLineEdit* world_id_;
        QLineEdit* world_name_;

      private slots:
        void do_cancel();
        void do_load();

    };

  } // namespace tools

} // namespace editor

#endif // EDITOR_TOOLS_SELECT_WORLD_HPP
