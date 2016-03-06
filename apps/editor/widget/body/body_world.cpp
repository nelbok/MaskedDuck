#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "editor/widget/body/body_world_view.hpp"
#include "editor/widget/body/body_world.hpp"

namespace editor
{

  namespace widget
  {

    body_world::body_world(editor_world_ptr w, QWidget* parent)
      : QWidget(parent)
      , world_(w)
      , view_(0)
    {
      init();
    }

    void body_world::init()
    {
      btn_world_.clear();

      QGridLayout* l = new QGridLayout(this);
      l->setContentsMargins(0, 0, 0, 0);
      l->setVerticalSpacing(4);
      l->setHorizontalSpacing(4);

      int nb_columns = 0;

      QLabel* lbl = new QLabel("World edition", this);
      l->addWidget(lbl, 0, nb_columns++, Qt::AlignCenter);

      // Buttons
      add_button(l, "Move", nb_columns++, SLOT(do_move_pushed()));
      add_button(l, "Edit", nb_columns++, SLOT(do_edit_pushed()));
      add_button(l, "Road", nb_columns++, SLOT(do_road_pushed()));
      add_button(l, "Remove", nb_columns++, SLOT(do_remove_pushed()));
      add_button(l, "Add a point", nb_columns++, SLOT(do_add_point_pushed()), ":/editor/nothing.png");
      add_button(l, "Add a level", nb_columns++, SLOT(do_add_level_pushed()), ":/editor/level.png");

      // Graphics View
      view_ = new widget::body_world_view(world_, this);
      l->addWidget(view_, 1, 0, 1, nb_columns);

      // StyleSheet
      setStyleSheet("QPushButton:flat { border: 1px solid; }");
    }

    void body_world::update_buttons(QObject* current)
    {
      for (int i = 0; i < btn_world_.size(); ++i)
      {
        QPushButton* btn = btn_world_.at(i);
        btn->setFlat(btn == current);
      }
    }

    QPushButton* body_world::add_button(QGridLayout* l, const QString& name, int column, const char* slot, const QString& icon)
    {
      QPushButton* btn = new QPushButton(name, this);
      btn->setIcon(QIcon(icon));
      btn->setMaximumWidth(80);
      btn_world_.append(btn);
      connect(btn, SIGNAL(clicked()), slot);
      l->addWidget(btn, 0, column);

      return btn;
    }


    void body_world::do_move_pushed()
    {
      view_->current_action(widget::body_world_view::MOVE);
      update_buttons(sender());
    }

    void body_world::do_edit_pushed()
    {
      view_->current_action(widget::body_world_view::EDIT);
      update_buttons(sender());
    }

    void body_world::do_road_pushed()
    {
      view_->current_action(widget::body_world_view::ROAD);
      update_buttons(sender());
    }

    void body_world::do_remove_pushed()
    {
      view_->current_action(widget::body_world_view::REMOVE);
      update_buttons(sender());
    }

    void body_world::do_add_point_pushed()
    {
      view_->current_action(widget::body_world_view::ADD_POINT);
      update_buttons(sender());
    }

    void body_world::do_add_level_pushed()
    {
      view_->current_action(widget::body_world_view::ADD_LEVEL);
      update_buttons(sender());
    }

  } // namespace widget

} // namespace editor
