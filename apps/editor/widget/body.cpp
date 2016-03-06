#include <QGridLayout>

#include "editor/widget/body/body_level.hpp"
#include "editor/widget/body/body_world.hpp"
#include "editor/widget/stages.hpp"
#include "editor/widget/body.hpp"

namespace editor
{

  namespace widget
  {

    body::body(QWidget* parent)
      : QWidget(parent)
      , current_(0)
    {
      layout_ = new QGridLayout(this);
      layout_->setContentsMargins(0, 0, 0, 0);
      layout_->setVerticalSpacing(0);
      layout_->setHorizontalSpacing(0);
    }


    void body::do_show_world(editor_world_ptr w)
    {
      if (current_)
      {
        current_->hide();
        current_->setParent(0);
        current_->deleteLater();
      }

      current_ = new widget::body_world(w, this);
      layout_->addWidget(current_, 0, 0);
    }

    void body::do_show_level(editor_world_ptr w, editor_level_ptr l)
    {
      if (current_)
      {
        current_->hide();
        current_->setParent(0);
        current_->deleteLater();
      }

      current_ = new widget::body_level(w, l, this);
      layout_->addWidget(current_, 0, 0);
    }

  } // namespace widget

} // namespace editor
