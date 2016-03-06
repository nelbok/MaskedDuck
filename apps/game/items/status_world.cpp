#include <QFont>
#include <QBrush>

#include "core/items/egg.hpp"
#include "core/items/life.hpp"

#include "game/items/status_world.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace items
  {

    status_world::status_world(game_player_ptr p)
      : p_(p)
    {
      init();
      update_text();
    }

    void status_world::update_text()
    {
      if (not p_->current_world())
        return;

      int id_world = p_->current_world()->id();

      world_->setHtml(QString("<center>World %1</center>").arg(id_world));
      eggs_->setHtml(QString("%1 / %2").arg(p_->nb_acquired_eggs(id_world)).arg(p_->max_eggs(id_world)));
      lifes_->setHtml(QString("%1 / %2").arg(p_->nb_acquired_lifes(id_world)).arg(p_->max_lifes(id_world)));
    }

    void status_world::init()
    {
      QFont f;
      f.setPixelSize(20);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Draw rect
      QGraphicsRectItem* r = new QGraphicsRectItem(-75, -40, 150, 80);
      r->setBrush(brush);
      addToGroup(r);

      // Draw level
      world_ = new QGraphicsTextItem();
      world_->setFont(f);
      world_->setPos(-75, -40);
      world_->setTextWidth(150);
      world_->setDefaultTextColor(QColor(Qt::white));
      addToGroup(world_);

      // Draw eggs
      addToGroup(new core::egg(0, QPoint(-55, -10)));
      eggs_ = new QGraphicsTextItem();
      eggs_->setFont(f);
      eggs_->setPos(-30, -15);
      eggs_->setTextWidth(100);
      eggs_->setDefaultTextColor(QColor(Qt::white));
      addToGroup(eggs_);

      // Draw lifes
      addToGroup(new core::life(0, QPoint(-55, 15)));
      lifes_ = new QGraphicsTextItem();
      lifes_->setFont(f);
      lifes_->setPos(-30, 10);
      lifes_->setTextWidth(100);
      lifes_->setDefaultTextColor(QColor(Qt::white));
      addToGroup(lifes_);
    }

  } // namespace items

} // namespace game
