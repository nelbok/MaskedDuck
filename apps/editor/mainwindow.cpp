#include <QGridLayout>

//FIXME
#include "../game/constant.hpp"

#include "editor/widget/body.hpp"
#include "editor/widget/items.hpp"
#include "editor/widget/menu.hpp"
#include "editor/widget/stages.hpp"
#include "editor/mainwindow.hpp"

namespace editor
{

  MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , world_(editor_world_ptr(new data::world))
  {
    // Init User Interface.
    setWindowTitle("Editor: "AMD_NAME);
    setWindowIcon(QIcon(":/core/life.png"));
    //FIXME
    //setFixedSize(1024, 768);

    // Main Menu.
    setMenuBar(new widget::menu(world_));

    // Main Widget.
    QWidget* w = new QWidget(this);
    QGridLayout* l = new QGridLayout(w);
    l->setContentsMargins(2, 2, 2, 2);
    l->setHorizontalSpacing(4);
    l->setVerticalSpacing(4);
    setCentralWidget(w);

    // List of the stage in the world.
    stages_ = new widget::stages(world_, w);
    l->addWidget(stages_, 0, 0);

    // Show the world or the stage.
    body_ = new widget::body(w);
    l->addWidget(body_, 0, 1, 2, 1);

    // List of the items in the resource.
    items_ = new widget::items(world_->resource(), w);
    l->addWidget(items_, 1, 0);

    connect(stages_, SIGNAL(sig_world_selected(editor_world_ptr)), body_, SLOT(do_show_world(editor_world_ptr)));
    connect(stages_, SIGNAL(sig_level_selected(editor_world_ptr, editor_level_ptr)), body_, SLOT(do_show_level(editor_world_ptr, editor_level_ptr)));
    body_->do_show_world(world_);
  }

  MainWindow::~MainWindow()
  {

  }

} // namespace editor
