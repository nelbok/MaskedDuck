#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>

#include "editor/widget/tools/edit_resource.hpp"

namespace editor
{

  namespace tools
  {

    edit_resource::edit_resource(int index, editor_resource_ptr r, QWidget* parent)
      : QDialog(parent)
      , resource_(r)
      , index_(index)
      , add_(false)
    {
      init();
    }

    edit_resource::edit_resource(editor_resource_ptr r, QWidget* parent)
      : QDialog(parent)
      , resource_(r)
      , index_(0)
      , add_(true)
    {
      init();
    }


    void edit_resource::init()
    {
      if (add_)
        setWindowTitle("Add a resource");
      else
        setWindowTitle("Edit the resource");
      setWindowIcon(QIcon(":/core/life.png"));
      setFixedSize(200, 150);
      setModal(true);


      QGridLayout* l = new QGridLayout(this);

      // Resource filename
      l->addWidget(new QLabel("Filename: ", this), 0, 0);
      res_filename_ = new QLineEdit(this);
      l->addWidget(res_filename_, 0, 1, 1, 2);

      // Resource type
      l->addWidget(new QLabel("Type: ", this), 1, 0);
      res_type_ = new QComboBox(this);
      res_type_->addItem(resource_->str_type_item(data::BACKGROUND));
      res_type_->addItem(resource_->str_type_item(data::DECOR));
      res_type_->addItem(resource_->str_type_item(data::SIGN));
      res_type_->addItem(resource_->str_type_item(data::DOOR));
      res_type_->addItem(resource_->str_type_item(data::BASEGROUND));
      res_type_->addItem(resource_->str_type_item(data::FOREGROUND));
      res_type_->addItem(resource_->str_type_item(data::DEATH_ITEM));
      l->addWidget(res_type_, 1, 1, 1, 2);

      // Edit mode
      if (not add_)
      {
        const data::item& res = resource_->item(index_);
        res_filename_->setText(res.filename_);
        res_type_->setCurrentIndex(res.type_);
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


    void edit_resource::do_cancel()
    {
      deleteLater();
    }

    void edit_resource::do_save()
    {
      if (add_)
        resource_->add_item(res_filename_->text(), data::type_item(res_type_->currentIndex()));
      else
      {
        data::item res = resource_->item(index_);
        res.filename_ = res_filename_->text();
        res.type_ = data::type_item(res_type_->currentIndex());
        resource_->replace_item(index_, res);
      }

      QMessageBox::information(this, "Save", "The resource was saved.", QMessageBox::Ok);
      deleteLater();
    }

  } // namespace tools

} // namespace editor
