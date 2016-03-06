#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>

#include "editor/widget/tools/select_resource.hpp"

namespace editor
{

  namespace tools
  {

    select_resource::select_resource(editor_resource_ptr r, QWidget* parent)
      : QDialog(parent)
      , resource_(r)
    {
      init();
    }


    void select_resource::init()
    {
      setWindowTitle("Select a resource");
      setWindowIcon(QIcon(":/core/life.png"));
      setFixedSize(200, 150);
      setModal(true);


      QGridLayout* l = new QGridLayout(this);

      // ComboBox
      type_ = new QComboBox(this);
      type_->addItem(resource_->str_type_item(data::DECOR),       QVariant(data::DECOR));
      type_->addItem(resource_->str_type_item(data::SIGN),        QVariant(data::SIGN));
      type_->addItem(resource_->str_type_item(data::BASEGROUND),  QVariant(data::BASEGROUND));
      type_->addItem(resource_->str_type_item(data::FOREGROUND),  QVariant(data::FOREGROUND));
      type_->addItem(resource_->str_type_item(data::DEATH_ITEM),  QVariant(data::DEATH_ITEM));
      //type_->addItem(QString("Other"));
      connect(type_, SIGNAL(currentIndexChanged(int)), SLOT(do_update_list()));
      l->addWidget(type_, 0, 0, 1, 3);
      // FIXME: Set current Index

      // ListWidget
      list_ = new QListWidget(this);
      list_->setViewMode(QListWidget::IconMode);
      do_update_list();
      l->addWidget(list_, 1, 0, 1, 3);

      // Buttons
      QPushButton* btn_cancel = new QPushButton("Cancel", this);
      btn_cancel->setMaximumWidth(80);
      l->addWidget(btn_cancel, 2, 1);
      connect(btn_cancel, SIGNAL(clicked()), SLOT(do_cancel()));

      QPushButton* btn_select = new QPushButton("Select", this);
      btn_select->setMaximumWidth(80);
      l->addWidget(btn_select, 2, 2);
      connect(btn_select, SIGNAL(clicked()), SLOT(do_select()));
    }


    void select_resource::do_update_list()
    {
      list_->clear();
      data::type_item type = data::type_item(type_->itemData(type_->currentIndex()).toInt());
      if (type == data::SIZE)
      {
        // Add egg / life item
      }
      else
      {
        const QList<data::item>& items = resource_->items();
        for (int i = 0; i < items.size(); ++i)
        {
          const data::item& item = items.at(i);
          if (item.type_ == type)
          {
            QListWidgetItem* lwi = new QListWidgetItem(QIcon(resource_->img_filename(item)), "", list_);
            lwi->setData(Qt::UserRole, QVariant(i));
          }
        }
      }
    }

    void select_resource::do_cancel()
    {
      deleteLater();
    }

    void select_resource::do_select()
    {
      if (QListWidgetItem* item = list_->currentItem())
        emit sig_resource_selected(item->data(Qt::UserRole).toInt());
      else
        emit sig_resource_selected(-1);

      deleteLater();
    }

  } // namespace tools

} // namespace editor
