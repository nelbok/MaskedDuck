#include <QFont>
#include <QBrush>

#include "core/items/egg.hpp"
#include "core/items/life.hpp"

#include "game/items/win_item.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace items
  {

    win_item::win_item(game_player_ptr p, const QList<int>& acquired_eggs, bool acquired_life)
      : p_(p)
      , acquired_eggs_(acquired_eggs)
      , acquired_life_(acquired_life)
    {
      init();
    }

    void win_item::init()
    {
      QFont f;
      f.setPixelSize(20);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Draw rect
      QGraphicsRectItem* r = new QGraphicsRectItem(-75, -60, 150, 120);
      r->setBrush(brush);
      addToGroup(r);

      // Draw text
      QGraphicsTextItem* text = new QGraphicsTextItem();
      text->setHtml("<center>Cleared level!</center>");
      text->setFont(f);
      text->setPos(-75, -60);
      text->setTextWidth(150);
      text->setDefaultTextColor(QColor(Qt::white));
      addToGroup(text);

      // Draw level
      QGraphicsTextItem* level = new QGraphicsTextItem();
      level->setHtml(QString("<center>%1 - %2</center>")
                     .arg(p_->current_world()->id())
                     .arg(p_->current_world_item()->level()->id()));
      level->setFont(f);
      level->setPos(-75, -20);
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
        if (acquired_eggs_.contains(i + 1))
          type = core::NEW_EGG;
        addToGroup(new core::egg(0, QPoint(x, 30), type));
        x += 30;
      }

      // Draw life
      const QList<bool>& llifes = p_->acquired_eggs();
      if (not llifes.empty())
      {
        core::type_life type = core::NO_LIFE;
        if (llifes.at(0))
          type = core::LIFE;
        if (acquired_life_)
          type = core::NEW_LIFE;
        addToGroup(new core::life(0, QPoint(-65, -15), type));
      }
    }

  } // namespace items

} // namespace game
