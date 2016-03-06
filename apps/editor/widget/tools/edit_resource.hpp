#ifndef EDITOR_TOOLS_EDIT_RESOURCE_HPP
# define EDITOR_TOOLS_EDIT_RESOURCE_HPP

# include <QDialog>

# include "editor/data/resource.hpp"

class QLineEdit;
class QComboBox;

namespace editor
{

  namespace tools
  {

    /*!
     *  Allow to edit or to add a resource in the world.\n
     *  A resource have a image defined by a filepath, a type and a identifying.
     */

    class edit_resource : public QDialog
    {
      Q_OBJECT

      public:
        edit_resource(int index, editor_resource_ptr r, QWidget* parent);
        edit_resource(editor_resource_ptr r, QWidget* parent);

      private:
        editor_resource_ptr resource_;
        int index_;
        bool add_;

        QLineEdit* res_filename_;
        QComboBox* res_type_;

        void init();

      private slots:
        void do_cancel();
        void do_save();
    };

  } // namespace tools

} // namespace editor

#endif // EDITOR_TOOLS_EDIT_RESOURCE_HPP
