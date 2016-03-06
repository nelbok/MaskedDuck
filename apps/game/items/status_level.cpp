#include <QFont>
#include <QBrush>

#include "core/items/egg.hpp"
#include "core/items/life.hpp"

#include "game/items/status_level.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace items
  {

    status_level::status_level(game_player_ptr p)
      : p_(p)
    {
      init();
    }

    void status_level::init()
    {
      QFont f;
      f.setPixelSize(20);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Draw rect
      QGraphicsRectItem* r = new QGraphicsRectItem(-75, -33, 150, 66);
      r->setBrush(brush);
      addToGroup(r);

      // Draw level
      QGraphicsTextItem* level = new QGraphicsTextItem();
      level->setHtml(QString("<center>%1 - %2</center>")
                     .arg(p_->current_world()->id())
                     .arg(p_->current_world_item()->level()->id()));
      level->setFont(f);
      level->setPos(-75, -33);
      level->setTextWidth(150);
      level->setDefaultTextColor(QColor(Qt::white));
      addToGroup(level);

      // Draw eggs
      int x = -70;
      const QList<bool>& leggs = p_->acquired_eggs();
      for (int i = 0; i < leggs.size(); ++i)
      {
        core::type_egg type = core::NO_EGG;
        if (leggs.at(i))
          type = core::EGG;
        addToGroup(new core::egg(0, QPoint(x, 0), type));
        x += 30;
      }

      // Draw life
      const QList<bool>& llifes = p_->acquired_eggs();
      if (not llifes.empty())
      {
        core::type_life type = core::NO_LIFE;
        if (llifes.at(0))
          type = core::LIFE;
        addToGroup(new core::life(0, QPoint(-65, -25), type));
      }

    }

  } // namespace items

} // namespace game
