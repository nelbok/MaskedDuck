#include <QBrush>
#include <QFont>

#include "core/items/egg.hpp"
#include "core/items/life.hpp"

#include "game/items/status_game.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace items
  {

    status_game::status_game(game_player_ptr p)
      : p_(p)
      , reset_mode_(false)
    {
      init();
      reinit();
      unfocus();
    }


    game_player_ptr status_game::player() const
    {
      return p_;
    }


    void status_game::reinit()
    {
      bool ng = p_->new_game();
      new_game_group_->setVisible(ng);
      continue_group_->setVisible(not ng);
      reset_mode_ = false;
      update_duck();
    }

    void status_game::change_option()
    {
      if (p_->new_game())
        return;
      reset_mode_ = not reset_mode_;
      update_duck();
    }

    bool status_game::reset_mode() const
    {
      return reset_mode_;
    }


    void status_game::focus()
    {
      focus_rect_->setVisible(true);
      duck_item_->setVisible(true);
      reset_mode_ = false;
      update_duck();
    }

    void status_game::unfocus()
    {
      focus_rect_->setVisible(false);
      duck_item_->setVisible(false);
    }


    void status_game::init()
    {
      QFont f;
      f.setPixelSize(20);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      QBrush w_brush;
      w_brush.setStyle(Qt::SolidPattern);
      w_brush.setColor(Qt::white);

      // Draw rect
      focus_rect_ = new QGraphicsRectItem(17, 17, AMD_SCENE_WIDTH - 34, 146);
      focus_rect_->setBrush(w_brush);
      addToGroup(focus_rect_);

      QGraphicsRectItem* r = new QGraphicsRectItem(20, 20, AMD_SCENE_WIDTH - 40, 140);
      r->setBrush(brush);
      addToGroup(r);

      // Draw level
      QGraphicsTextItem* level = new QGraphicsTextItem();
      level->setHtml(QString("<i>%1</i>").arg(p_->id()));
      level->setFont(f);
      level->setPos(30, 30);
      level->setDefaultTextColor(QColor(Qt::white));
      addToGroup(level);

      // New game group

      new_game_group_ = new QGraphicsItemGroup();

      QGraphicsTextItem* newgame_text = new QGraphicsTextItem();
      newgame_text->setHtml(QString("<center>New game</center>"));
      newgame_text->setFont(f);
      newgame_text->setPos(140, 120);
      newgame_text->setTextWidth(200);
      newgame_text->setDefaultTextColor(QColor(Qt::white));
      new_game_group_->addToGroup(newgame_text);

      addToGroup(new_game_group_);

      // Continue group

      continue_group_ = new QGraphicsItemGroup();

      QGraphicsTextItem* continue_text = new QGraphicsTextItem();
      continue_text->setHtml(QString("<center>Continue</center>"));
      continue_text->setFont(f);
      continue_text->setPos(140, 120);
      continue_text->setTextWidth(200);
      continue_text->setDefaultTextColor(QColor(Qt::white));
      continue_group_->addToGroup(continue_text);

      QGraphicsTextItem* delete_text = new QGraphicsTextItem();
      delete_text->setHtml(QString("<center>Delete</center>"));
      delete_text->setFont(f);
      delete_text->setPos(440, 120);
      delete_text->setTextWidth(200);
      delete_text->setDefaultTextColor(QColor(Qt::white));
      continue_group_->addToGroup(delete_text);

      // Draw lifes
      continue_group_->addToGroup(new core::life(0, QPoint(150, 75)));
      QGraphicsTextItem* lifes_ = new QGraphicsTextItem();
      lifes_->setFont(f);
      lifes_->setPos(170, 70);
      lifes_->setTextWidth(70);
      lifes_->setDefaultTextColor(QColor(Qt::white));
      lifes_->setHtml(QString("x %1").arg(p_->lifes()));
      continue_group_->addToGroup(lifes_);

      // Draw eggs
      continue_group_->addToGroup(new core::egg(0, QPoint(240, 75)));
      QGraphicsTextItem* eggs_ = new QGraphicsTextItem();
      eggs_->setFont(f);
      eggs_->setPos(260, 70);
      eggs_->setTextWidth(70);
      eggs_->setDefaultTextColor(QColor(Qt::white));
      eggs_->setHtml(QString("x %1").arg(p_->nb_acquired_eggs()));
      continue_group_->addToGroup(eggs_);

      addToGroup(continue_group_);

      // Duck item
      duck_item_ = new core::life(0, QPoint(0, 0));
      addToGroup(duck_item_);
    }

    void status_game::update_duck()
    {
      if (not reset_mode_)
        duck_item_->setPos(100, 125);
      else
        duck_item_->setPos(400, 125);
    }

  } // namespace items

} // namespace game
