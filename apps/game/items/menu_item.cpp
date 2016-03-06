#include <QFont>
#include <QBrush>

#include "core/items/life.hpp"

#include "game/items/menu_item.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace items
  {

    menu_item::menu_item(menu_item::menu_type type)
      : current_choice_(0)
      , duck_(0)
      , type_(type)
    {
      nb_choices_ = 4;
      init();
    }


    void menu_item::move_to_up()
    {
      if (current_choice_ == 0)
        current_choice_ = nb_choices_ - 1;
      else
        --current_choice_;

      move_duck();
    }

    void menu_item::move_to_down()
    {
      if (current_choice_ == nb_choices_ - 1)
        current_choice_ = 0;
      else
        ++current_choice_;

      move_duck();
    }


    menu_item::selection_type menu_item::current_selection() const
    {
      switch (type_)
      {
        case SCENE_LEVEL:
          if (current_choice_ == 0) return menu_item::CONTINUE;
          if (current_choice_ == 1) return menu_item::QUIT_LEVEL;
          if (current_choice_ == 2) return menu_item::QUIT_GAME;
          break;
        case SCENE_WORLD:
          if (current_choice_ == 0) return menu_item::CONTINUE;
          if (current_choice_ == 1) return menu_item::RETURN_MAP;
          if (current_choice_ == 2) return menu_item::QUIT_GAME;
          break;
        case SELECT_WORLD:
          if (current_choice_ == 0) return menu_item::CONTINUE;
          if (current_choice_ == 1) return menu_item::QUIT_GAME;
          break;
      }

      return menu_item::CONTINUE;
    }


    void menu_item::init()
    {
      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      switch (type_)
      {
        case SCENE_LEVEL:
          nb_choices_ = 3;
          break;
        case SCENE_WORLD:
          nb_choices_ = 3;
          break;
        case SELECT_WORLD:
          nb_choices_ = 2;
          break;
      }

      // Draw rect
      QGraphicsRectItem* r = new QGraphicsRectItem(-AMD_SCENE_WIDTH / 6, -AMD_CHOICE_HEIGHT * nb_choices_ / 2, AMD_SCENE_WIDTH / 3, AMD_CHOICE_HEIGHT * nb_choices_);
      r->setBrush(brush);
      addToGroup(r);

      switch (type_)
      {
        case SCENE_LEVEL:
          draw_text("Continue",                     AMD_CHOICE_HEIGHT * 0);
          draw_text("Quit the level (lose 1 life)", AMD_CHOICE_HEIGHT * 1);
          draw_text("Quit the game",                AMD_CHOICE_HEIGHT * 2);
          break;
        case SCENE_WORLD:
          draw_text("Continue",                     AMD_CHOICE_HEIGHT * 0);
          draw_text("Return to the map",            AMD_CHOICE_HEIGHT * 1);
          draw_text("Quit the game",                AMD_CHOICE_HEIGHT * 2);
          break;
        case SELECT_WORLD:
          draw_text("Continue",                     AMD_CHOICE_HEIGHT * 0);
          draw_text("Quit the game",                AMD_CHOICE_HEIGHT * 1);
          break;
      }

      // Draw choice
      duck_ = new core::life(0, QPoint(0, 0));
      move_duck();
      addToGroup(duck_);
    }

    void menu_item::draw_text(const QString& text, int y_offset)
    {
      QFont f;
      f.setPixelSize(12);

      // Draw text
      QGraphicsTextItem* item = new QGraphicsTextItem();
      item->setHtml(text);
      item->setFont(f);
      item->setPos(-AMD_SCENE_WIDTH / 6 + 40, -AMD_CHOICE_HEIGHT * nb_choices_ / 2 + y_offset);
      item->setTextWidth(AMD_SCENE_WIDTH / 3);
      item->setDefaultTextColor(QColor(Qt::white));
      addToGroup(item);
    }

    void menu_item::move_duck()
    {
      duck_->setPos(-AMD_SCENE_WIDTH / 6 + 5, -AMD_CHOICE_HEIGHT * nb_choices_ / 2 + 5 + AMD_CHOICE_HEIGHT * current_choice_);
    }

  } // namespace items

} // namespace game
