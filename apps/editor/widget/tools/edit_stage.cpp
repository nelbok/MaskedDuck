#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "editor/data/stage/level.hpp"
#include "editor/widget/tools/edit_stage.hpp"

namespace editor
{

  namespace tools
  {

    edit_stage::edit_stage(editor_world_ptr w, core::world_item::item_type type, const QPoint& pos, QWidget* parent)
      : QDialog(parent)
      , world_(w)
      , type_(type)
      , pos_(pos)
      , add_(true)
    {
      init();
    }

    edit_stage::edit_stage(editor_world_ptr w, world_item_ptr item, QWidget* parent)
      : QDialog(parent)
      , world_(w)
      , data_(item)
      , type_(item->type())
      , pos_(item->pos())
      , add_(false)
    {
      init();
    }

    void edit_stage::init()
    {
      if (add_)
        setWindowTitle("Add a stage");
      else
        setWindowTitle("Edit the stage");
      setWindowIcon(QIcon(":/core/life.png"));
      setFixedSize(200, 150);
      setModal(true);


      QGridLayout* l = new QGridLayout(this);

      // Stage id
      l->addWidget(new QLabel("Id: ", this), 0, 0);
      res_id_ = new QLineEdit(this);
      l->addWidget(res_id_, 0, 1, 1, 2);

      // Stage name
      l->addWidget(new QLabel("Name: ", this), 1, 0);
      res_name_ = new QLineEdit(this);
      l->addWidget(res_name_, 1, 1, 1, 2);

      // Edit mode
      if (not add_)
      {
        res_id_->setText(QString::number(data_->stage()->id()));
        res_name_->setText(data_->stage()->name());
      }

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

    void edit_stage::do_cancel()
    {
      deleteLater();
    }


    void edit_stage::do_save()
    {
      int id = res_id_->text().toInt();
      const QString& name = res_name_->text();

      if (add_)
      {
        //FIXME: Missing pnj/boss
        switch(type_)
        {
          case core::world_item::NONE:    break;
          case core::world_item::RETURN:  break;
          case core::world_item::LEVEL:
          {
            editor_level_ptr item = editor_level_ptr(new data::level(*(world_.data()), id, name));
            world_->add_world_item(pos_, item);
            break;
          }
          case core::world_item::BOSS:    break;
          case core::world_item::PNJ:     break;
        }
      }
      else
      {
        world_->modify_world_item(data_, id, name);
      }

      QMessageBox::information(this, "Save", "The stage was saved.", QMessageBox::Ok);
      deleteLater();
    }

  } // namespace tools

} // namespace editor
