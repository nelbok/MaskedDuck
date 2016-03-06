#include <QFont>
#include <QBrush>

#include "game/items/lose_item.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace items
  {

    lose_item::lose_item()
    {
      init();
    }

    void lose_item::init()
    {
      QFont f;
      f.setPixelSize(20);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Draw rect
      QGraphicsRectItem* r = new QGraphicsRectItem(0, -15, AMD_SCENE_WIDTH, 30);
      r->setBrush(brush);
      addToGroup(r);

      //Draw text
      QGraphicsTextItem* text = new QGraphicsTextItem();
      text->setHtml("<center>You lose!</center>");
      text->setFont(f);
      text->setPos(0, -15);
      text->setTextWidth(AMD_SCENE_WIDTH);
      text->setDefaultTextColor(QColor(Qt::white));
      addToGroup(text);
    }
  } // namespace items

} // namespace game
