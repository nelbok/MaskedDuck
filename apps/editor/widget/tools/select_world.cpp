#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

#include "editor/widget/tools/select_world.hpp"

namespace editor
{

  namespace tools
  {

    select_world::select_world(editor_world_ptr w, QWidget* parent)
      : QDialog(parent)
      , world_(w)
    {
      setWindowTitle("Load the world");
      setWindowIcon(QIcon(":/core/life.png"));
      setFixedSize(200, 150);
      setModal(true);

      QGridLayout* l = new QGridLayout(this);

      // World id
      l->addWidget(new QLabel("Id: ", this), 0, 0);
      world_id_ = new QLineEdit(this);
      world_id_->setText(QString::number(world_->id()));
      l->addWidget(world_id_, 0, 1, 1, 2);

      // Buttons
      QPushButton* btn_cancel = new QPushButton("Cancel", this);
      btn_cancel->setMaximumWidth(80);
      l->addWidget(btn_cancel, 1, 1);
      connect(btn_cancel, SIGNAL(clicked()), SLOT(do_cancel()));

      QPushButton* btn_load = new QPushButton("Load", this);
      btn_load->setMaximumWidth(80);
      l->addWidget(btn_load, 1, 2);
      connect(btn_load, SIGNAL(clicked()), SLOT(do_load()));
    }


    void select_world::do_cancel()
    {
      deleteLater();
    }

    void select_world::do_load()
    {
      world_->id(world_id_->text().toInt());
      world_->load();
      QMessageBox::information(this, "Load", "The project was loaded.", QMessageBox::Ok);
      deleteLater();
    }

  } // namespace tools

} // namespace editor
