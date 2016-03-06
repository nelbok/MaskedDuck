#ifndef EDITOR_MAINWINDOW_HPP
# define EDITOR_MAINWINDOW_HPP

# include <QMainWindow>

# include "editor/data/world.hpp"

class QGraphicsView;
class QGraphicsScene;
class QGridLayout;

namespace editor
{

  namespace widget
  {
    class header;
    class body;
    class items;
    class stages;
  } // namespace widget

  /*!
   *  Main window of the editor.
   */

  class MainWindow : public QMainWindow
  {
    Q_OBJECT

    public:
      MainWindow(QWidget *parent = 0);
      ~MainWindow();

    private:
      editor_world_ptr world_;
      widget::header* header_;
      widget::body* body_;
      widget::stages* stages_;
      widget::items* items_;
  };

} // namespace editor

#endif // EDITOR_MAINWINDOW_HPP
