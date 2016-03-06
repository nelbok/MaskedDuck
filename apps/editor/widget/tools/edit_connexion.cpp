#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "editor/widget/tools/edit_connexion.hpp"

namespace editor
{

  namespace tools
  {

    edit_connexion::edit_connexion(editor_world_ptr w, world_item_ptr w1, world_item_ptr w2, QWidget* parent)
      : QDialog(parent)
      , world_(w)
      , w1_(w1)
      , w2_(w2)
    {
      add_ = not w1->contains_connexion(w2);

      init();
    }

    void edit_connexion::init()
    {
      if (add_)
        setWindowTitle("Add a connexion");
      else
        setWindowTitle("Edit the connexion");
      setWindowIcon(QIcon(":/core/life.png"));
      setFixedSize(200, 150);
      setModal(true);


      QGridLayout* l = new QGridLayout(this);

      // Resource id door
      l->addWidget(new QLabel("Id door: ", this), 0, 0);
      res_id_door_ = new QLineEdit(this);
      l->addWidget(res_id_door_, 0, 1, 1, 2);

      // Edit mode
      if (not add_)
        res_id_door_->setText(QString::number(w1_->connexions().value(w2_)));

      // Buttons
      QPushButton* btn_cancel = new QPushButton("Cancel", this);
      btn_cancel->setMaximumWidth(80);
      l->addWidget(btn_cancel, 1, 1);
      connect(btn_cancel, SIGNAL(clicked()), SLOT(do_cancel()));

      QPushButton* btn_save = new QPushButton("Save", this);
      btn_save->setMaximumWidth(80);
      l->addWidget(btn_save, 1, 2);
      connect(btn_save, SIGNAL(clicked()), SLOT(do_save()));
    }

    void edit_connexion::do_cancel()
    {
      deleteLater();
    }


    void edit_connexion::do_save()
    {
      int id_door = res_id_door_->text().toInt();

      if (add_)
      {
        world_->add_world_item_connexion(w1_, w2_, id_door);
      }
      else
      {
        world_->modify_world_item_connexion(w1_, w2_, id_door);
      }

      QMessageBox::information(this, "Save", "The connexion was saved.", QMessageBox::Ok);
      deleteLater();
    }

  } // namespace tools

} // namespace editor
