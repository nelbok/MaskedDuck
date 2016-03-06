#ifndef EDITOR_TOOLS_SELECT_RESOURCE_HPP
# define EDITOR_TOOLS_SELECT_RESOURCE_HPP

# include <QDialog>

# include "editor/data/resource.hpp"

class QListWidget;
class QComboBox;

namespace editor
{

  namespace tools
  {

    /*!
     *  Select a resource and emit the result.
     */

    class select_resource : public QDialog
    {
      Q_OBJECT

      public:
        select_resource(editor_resource_ptr r, QWidget* parent);

      private:
        editor_resource_ptr resource_;
        QListWidget* list_;
        QComboBox* type_;

        void init();

      private slots:
        void do_update_list();
        void do_cancel();
        void do_select();

      signals:
        /*! Signal emitted when the user valid his choice.
         * \param index Index of the resource.
         */
        void sig_resource_selected(int index);
    };

  } // namespace tools

} // namespace editor

#endif // EDITOR_TOOLS_SELECT_RESOURCE_HPP
