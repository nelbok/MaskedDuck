#ifndef EDITOR_TOOLS_EDIT_STAGE_HPP
# define EDITOR_TOOLS_EDIT_STAGE_HPP

# include <QDialog>

# include "core/world_item.hpp"

# include "editor/data/world.hpp"

class QLineEdit;

namespace editor
{

  namespace tools
  {

    /*!
     *  Allow to edit or to add a stage.\n
     *  A stage have a position, a name and a identifying.
     */

    class edit_stage : public QDialog
    {
      Q_OBJECT

      public:
        edit_stage(editor_world_ptr, core::world_item::item_type type, const QPoint& pos, QWidget* parent);
        edit_stage(editor_world_ptr, world_item_ptr, QWidget* parent);

      private:
        editor_world_ptr world_;
        world_item_ptr data_;
        core::world_item::item_type type_;
        QPoint pos_;
        bool add_;

        QLineEdit* res_id_;
        QLineEdit* res_name_;

        void init();

      private slots:
        void do_cancel();
        void do_save();
    };

  } // namespace tools

} // namespace editor

#endif // EDITOR_TOOLS_EDIT_STAGE_HPP
