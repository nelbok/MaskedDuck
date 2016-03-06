#ifndef EDITOR_WIDGET_BODY_HPP
# define EDITOR_WIDGET_BODY_HPP

# include <QWidget>

# include "editor/data/stage/level.hpp"
# include "editor/data/world.hpp"

class QGridLayout;

namespace editor
{

  namespace widget
  {
    class stages;

    /*!
     *  Body of the editor.\n
     *  Show the view of a world or a stage
     */

    class body : public QWidget
    {
      Q_OBJECT

      public:
        body(QWidget* parent = 0);

      public slots:
        /*!
         *  Show the view of a world
         * \param w Instance of a world
         */
        void do_show_world(editor_world_ptr w);
        /*!
         *  Show the view of a level
         * \param w Instance of a world
         * \param l Instance of a level
         */
        void do_show_level(editor_world_ptr w, editor_level_ptr l);

      private:
        QGridLayout* layout_;
        QWidget* current_;

    };

  } // namespace widget

} // namespace editor

#endif // EDITOR_WIDGET_BODY_HPP
