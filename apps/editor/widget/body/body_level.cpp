#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "editor/widget/tools/select_resource.hpp"
#include "editor/widget/body/body_level_view.hpp"
#include "editor/widget/body/body_level.hpp"

namespace editor
{

  namespace widget
  {

    body_level::body_level(editor_world_ptr w, editor_level_ptr l, QWidget* parent)
      : QWidget(parent)
      , world_(w)
      , level_(l)
      , view_(0)
    {
      init();
    }

    void body_level::init()
    {
      btn_level_.clear();

      QGridLayout* l = new QGridLayout(this);
      l->setContentsMargins(0, 0, 0, 0);
      l->setVerticalSpacing(4);
      l->setHorizontalSpacing(4);

      int nb_columns = 0;

      QLabel* lbl = new QLabel("level edition", this);
      l->addWidget(lbl, 0, nb_columns++, Qt::AlignCenter);

      // Buttons
      btn_add_ = add_button(l, "Add", nb_columns++, SLOT(do_add_pushed()));
      connect(world_->resource().data(), SIGNAL(sig_resource_updated()), SLOT(do_reset_add_button()));
      add_button(l, "Remove", nb_columns++, SLOT(do_remove_pushed()));

      // Graphics View
      view_ = new widget::body_level_view(world_, level_, this);
      l->addWidget(view_, 1, 0, 1, nb_columns);

      // StyleSheet
      setStyleSheet("QPushButton:flat { border: 1px solid; }");
    }

    void body_level::update_buttons(QObject* current)
    {
      for (int i = 0; i < btn_level_.size(); ++i)
      {
        QPushButton* btn = btn_level_.at(i);
        btn->setFlat(btn == current);
      }
    }

    QPushButton* body_level::add_button(QGridLayout* l, const QString& name, int column, const char* slot, const QString& icon)
    {
      QPushButton* btn = new QPushButton(name, this);
      btn->setIcon(QIcon(icon));
      btn->setMaximumWidth(80);
      btn_level_.append(btn);
      connect(btn, SIGNAL(clicked()), slot);
      l->addWidget(btn, 0, column);

      return btn;
    }


    void body_level::do_add_pushed()
    {
      view_->current_action(widget::body_level_view::ADD);
      update_buttons(sender());

      tools::select_resource* w = new tools::select_resource(world_->resource(), this);
      connect(w, SIGNAL(sig_resource_selected(int)), SLOT(do_update_add_button(int)));
      w->show();
    }

    void body_level::do_reset_add_button()
    {
      do_update_add_button(-1);
    }

    void body_level::do_update_add_button(int index)
    {
      // Change the icon for the add button in function of the current resource.
      if (index >= 0)
      {
        editor_resource_ptr resource = world_->resource();
        const data::item& res = resource->item(index);
        btn_add_->setIcon(QIcon(resource->img_filename(res)));
        view_->res_add(res);
      }
      else
      {
        btn_add_->setIcon(QIcon());
        view_->reset_res_add();
      }
    }

    void body_level::do_remove_pushed()
    {
      view_->current_action(widget::body_level_view::REMOVE);
      update_buttons(sender());
    }

  } // namespace widget

} // namespace editor
