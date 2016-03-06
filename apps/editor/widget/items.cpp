#include <QGridLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

#include "editor/widget/tools/edit_resource.hpp"
#include "editor/widget/items.hpp"

namespace editor
{

  namespace widget
  {

    items::items(editor_resource_ptr res, QWidget* parent)
      : QFrame(parent)
      , resource_(res)
    {
      setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

      QGridLayout* l = new QGridLayout(this);
      l->setContentsMargins(0, 0, 0, 0);

      // Tablewidget
      data_ = new QTableWidget(this);

      data_->setColumnCount(3);
      data_->setHorizontalHeaderLabels(QStringList() << "Filename" << "Type" << "?");
      data_->setColumnWidth(0, 100);
      data_->setColumnWidth(1, 75);
      data_->setColumnWidth(2, 20);

      data_->verticalHeader()->setVisible(false);

      data_->setEditTriggers(QTableWidget::NoEditTriggers);
      data_->setSelectionMode(QTableWidget::SingleSelection);
      data_->setSelectionBehavior(QTableWidget::SelectRows);
      data_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

      l->addWidget(data_, 0, 0, 1, 2);

      // Buttons
      QPushButton* btn_edit = new QPushButton("Edit", this);
      btn_edit->setMaximumWidth(80);
      l->addWidget(btn_edit, 2, 0, Qt::AlignCenter);
      connect(btn_edit, SIGNAL(clicked()), SLOT(do_edit()));

      QPushButton* btn_add = new QPushButton("Add", this);
      btn_add->setMaximumWidth(80);
      l->addWidget(btn_add, 1, 0, Qt::AlignCenter);
      connect(btn_add, SIGNAL(clicked()), SLOT(do_add()));

      QPushButton* btn_remove = new QPushButton("Remove", this);
      btn_remove->setMaximumWidth(80);
      l->addWidget(btn_remove, 1, 1, Qt::AlignCenter);
      connect(btn_remove, SIGNAL(clicked()), SLOT(do_remove()));

      QPushButton* btn_generate = new QPushButton("Generate", this);
      btn_generate->setMaximumWidth(80);
      l->addWidget(btn_generate, 2, 1, Qt::AlignCenter);
      connect(btn_generate, SIGNAL(clicked()), SLOT(do_generate()));

      connect(resource_.data(), SIGNAL(sig_resource_updated()), SLOT(do_update()));
      do_update();
    }


    void items::do_update()
    {
      const QList<data::item>& items = resource_->items();
      int size = items.size();

      data_->clearContents();
      data_->setRowCount(size);

      for (int i = 0; i < size; ++i)
      {
        data::item res = items.at(i);

        QTableWidgetItem* tfn = new QTableWidgetItem(res.filename_);
        tfn->setData(Qt::UserRole, QVariant(res.id_));
        tfn->setToolTip(res.filename_);
        data_->setItem(i, 0, tfn);

        QTableWidgetItem* tt = new QTableWidgetItem(resource_->str_type_item(res.type_));
        tt->setData(Qt::UserRole, QVariant(res.id_));
        data_->setItem(i, 1, tt);

        QTableWidgetItem* to = new QTableWidgetItem();
        to->setData(Qt::UserRole, QVariant(res.id_));
        data_->setItem(i, 2, to);
      }
    }


    void items::do_edit()
    {
      (new tools::edit_resource(data_->currentRow(), resource_, this))->show();
    }

    void items::do_add()
    {
      (new tools::edit_resource(resource_, this))->show();
    }

    void items::do_remove()
    {
      resource_->remove_item(data_->currentRow());
      QMessageBox::information(this, "Remove", "The resource was removed.", QMessageBox::Ok);
    }

    void items::do_generate()
    {
      resource_->generate();
      QMessageBox::information(this, "Generate", "The resource was generated.", QMessageBox::Ok);
    }

  } // namespace widget

} // namespace editor
