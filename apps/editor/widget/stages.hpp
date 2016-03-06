#ifndef EDITOR_WIDGET_STAGES_HPP
# define EDITOR_WIDGET_STAGES_HPP

# include <QFrame>

# include "editor/data/stage/level.hpp"
# include "editor/data/world.hpp"

class QListWidget;
class QListWidgetItem;

namespace editor
{

  namespace widget
  {

    /*!
     *  Stages of the editor.\n
     *  List the stages in a world
     */

    class stages : public QFrame
    {
      Q_OBJECT

      public:
        stages(editor_world_ptr w, QWidget* parent = 0);

      private:
        editor_world_ptr world_;
        QListWidget* list_;
        bool update_;

        template<class T>
        QListWidgetItem* add_stage_item(T data, const QString& text);

      private slots:
        void do_update_list();
        void do_selection_changed();

      signals:
        /*! Signal emitted when the user select the world.
         * \param w Instance of a world
         */
        void sig_world_selected(editor_world_ptr w);
        /*! Signal emitted when the user select a level.
         * \param w Instance of a world
         * \param l Instance of a level
         */
        void sig_level_selected(editor_world_ptr w, editor_level_ptr l);
    };

  } // namespace widget

} // namespace editor

#endif // EDITOR_WIDGET_STAGES_HPP
