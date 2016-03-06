#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

#include "editor/widget/tools/edit_world.hpp"

namespace editor
{

  namespace tools
  {

    edit_world::edit_world(editor_world_ptr w, QWidget* parent)
      : QDialog(parent)
      , world_(w)
    {
      setWindowTitle("Edit the world");
      setWindowIcon(QIcon(":/core/life.png"));
      setFixedSize(200, 150);
      setModal(true);

      QGridLayout* l = new QGridLayout(this);

      // World id
      l->addWidget(new QLabel("Id: ", this), 0, 0);
      world_id_ = new QLineEdit(this);
      world_id_->setText(QString::number(world_->id()));
      l->addWidget(world_id_, 0, 1, 1, 2);

      // World name
      l->addWidget(new QLabel("Name: ", this), 1, 0);
      world_name_ = new QLineEdit(this);
      world_name_->setText(world_->name());
      l->addWidget(world_name_, 1, 1, 1, 2);

      // Buttons
      QPushButton* btn_cancel = new QPushButton("Cancel", this);
      btn_cancel->setMaximumWidth(80);
      l->addWidget(btn_cancel, 2, 1);
      connect(btn_cancel, SIGNAL(clicked()), SLOT(do_cancel()));

      QPushButton* btn_save = new QPushButton("Save", this);
      btn_save->setMaximumWidth(80);
      l->addWidget(btn_save, 2, 2);
      connect(btn_save, SIGNAL(clicked()), SLOT(do_save()));
    }


    void edit_world::do_cancel()
    {
      deleteLater();
    }

    void edit_world::do_save()
    {
      world_->id(world_id_->text().toInt());
      world_->name(world_name_->text());
      QMessageBox::information(this, "Save", "The world was saved.", QMessageBox::Ok);
      deleteLater();
    }

  } // namespace tools

} // namespace editor
