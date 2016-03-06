#include <QGridLayout>
#include <QLabel>
#include <QListWidget>

#include "editor/widget/stages.hpp"

Q_DECLARE_METATYPE(editor_world_ptr)
Q_DECLARE_METATYPE(editor_level_ptr)

namespace editor
{

  namespace widget
  {

    stages::stages(editor_world_ptr w, QWidget *parent)
      : QFrame(parent)
      , world_(w)
      , update_(false)
    {
      setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

      QGridLayout* l = new QGridLayout(this);
      l->setContentsMargins(0, 0, 0, 0);
      list_ = new QListWidget(this);
      list_->setSelectionMode(QAbstractItemView::SingleSelection);
      connect(list_, SIGNAL(itemSelectionChanged()), SLOT(do_selection_changed()));
      l->addWidget(list_);

      connect(world_.data(), SIGNAL(sig_world_updated()), SLOT(do_update_list()));
      do_update_list();
    }


    template<class T>
    QListWidgetItem* stages::add_stage_item(T data, const QString& text)
    {
      QListWidgetItem* item = new QListWidgetItem(text);
      item->setData(Qt::UserRole, QVariant::fromValue(data));
      list_->addItem(item);
      return item;
    }


    void stages::do_update_list()
    {
      update_ = true;

      editor_level_ptr current_l;
      if (QListWidgetItem* item = list_->currentItem())
        current_l = item->data(Qt::UserRole).value<editor_level_ptr>();

      list_->clear();

      // Add world item
      QListWidgetItem* current_item = add_stage_item(world_, "world");

      const QList<world_item_ptr>& items = world_->world_items();
      for (int i = 0; i < items.size(); ++i)
      {
        world_item_ptr wi = items.at(i);
        // FIXME: Missing pnj/boss
        if (editor_level_ptr l = world_->get_level(wi))
        {
          QListWidgetItem* item = add_stage_item(l, QString("level%2").arg(l->id()));
          if (current_l == l)
            current_item = item;
        }
      }

      list_->setCurrentItem(current_item);

      update_ = false;
    }

    void stages::do_selection_changed()
    {
      if (update_)
        return;

      QListWidgetItem* current = list_->currentItem();
      if (editor_world_ptr w = current->data(Qt::UserRole).value<editor_world_ptr>())
        emit sig_world_selected(w);
      if (editor_level_ptr l = current->data(Qt::UserRole).value<editor_level_ptr>())
        emit sig_level_selected(world_, l);
    }

  } // namespace widget

} // namespace editor
