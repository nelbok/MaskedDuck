#ifndef EDITOR_TOOLS_EDIT_CONNEXION_HPP
# define EDITOR_TOOLS_EDIT_CONNEXION_HPP

# include <QDialog>

# include "core/world_item.hpp"

# include "editor/data/world.hpp"

class QLineEdit;

namespace editor
{

  namespace tools
  {

    /*!
     *  Allow to edit a connexion between two world item.\n
     *  You can only modify the identifying of the door.\n
     *  Set 0 if there are not a door.
     */

    class edit_connexion : public QDialog
    {
      Q_OBJECT

      public:
        edit_connexion(editor_world_ptr w, world_item_ptr w1, world_item_ptr w2, QWidget* parent);

      private:
        editor_world_ptr world_;
        world_item_ptr w1_;
        world_item_ptr w2_;
        bool add_;

        QLineEdit* res_id_door_;

        void init();

      private slots:
        void do_cancel();
        void do_save();
    };

  } // namespace tools

} // namespace editor

#endif // EDITOR_TOOLS_EDIT_CONNEXION_HPP
