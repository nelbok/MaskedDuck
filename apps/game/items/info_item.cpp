#include <QFont>
#include <QBrush>

#include "core/items/egg.hpp"
#include "core/items/life.hpp"

#include "game/items/info_item.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace items
  {

    info_item::info_item(game_player_ptr p)
      : life_text_(0)
      , place_text_(0)
      , egg_text_(0)
      , player_(p)
    {
      init();
      update_text();
    }


    void info_item::update_text()
    {
      world_ptr w = player_->current_world();
      stage_ptr s;
      if (world_item_ptr wi = player_->current_world_item())
        if (wi->is_stage())
          s = wi->stage();

      life_text_->setHtml(QString("x %1").arg(player_->lifes()));

      QString str_text;
      if (w) str_text.append(w->name());
      if (s) str_text.append(QString(" - %2").arg(s->name()));
      place_text_->setHtml(QString("<center>%1</center>").arg(str_text));

      egg_text_->setHtml(QString("x %1").arg(player_->nb_acquired_eggs()));
    }


    void info_item::init()
    {
      QFont f;
      f.setPixelSize(20);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Draw rect information
      QGraphicsRectItem* r = new QGraphicsRectItem(0, 0, AMD_SCENE_WIDTH, 30);
      r->setBrush(brush);
      addToGroup(r);

      // Draw life
      addToGroup(new core::life(0, QPoint(5, 5)));
      life_text_ = new QGraphicsTextItem();
      life_text_->setFont(f);
      life_text_->setPos(30, 0);
      life_text_->setTextWidth(70);
      life_text_->setDefaultTextColor(QColor(Qt::white));
      addToGroup(life_text_);

      // Draw text world / level
      place_text_ = new QGraphicsTextItem();
      place_text_->setFont(f);
      place_text_->setPos(100, 0);
      place_text_->setTextWidth(600);
      place_text_->setDefaultTextColor(QColor(Qt::white));
      addToGroup(place_text_);

      // Draw id world / level
      addToGroup(new core::egg(0, QPoint(705, 5)));
      egg_text_ = new QGraphicsTextItem();
      egg_text_->setFont(f);
      egg_text_->setPos(730, 0);
      egg_text_->setTextWidth(70);
      egg_text_->setDefaultTextColor(QColor(Qt::white));
      addToGroup(egg_text_);
    }
  } // namespace items

} // namespace game
