#ifndef EDITOR_TOOLS_EDIT_WORLD_HPP
# define EDITOR_TOOLS_EDIT_WORLD_HPP

# include <QDialog>

# include "editor/data/world.hpp"

class QLineEdit;

namespace editor
{

  namespace tools
  {

    /*!
     *  Allow to edit the world.\n
     *  A world have a name and a identifying.
     */

    class edit_world : public QDialog
    {
      Q_OBJECT

      public:
        edit_world(editor_world_ptr w, QWidget* parent);

      private:
        editor_world_ptr world_;

        QLineEdit* world_id_;
        QLineEdit* world_name_;

      private slots:
        void do_cancel();
        void do_save();

    };

  } // namespace tools

} // namespace editor

#endif // EDITOR_TOOLS_EDIT_WORLD_HPP
