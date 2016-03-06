#include <QKeyEvent>
#include <QGraphicsItem>

#include "game/scene/game_over.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace scene
  {

    game_over::game_over()
    {
      load();
    }


    void game_over::keyPressEvent(QKeyEvent* e)
    {
      if (e->isAutoRepeat())
        return;

      switch (e->key())
      {
        case Qt::Key_Return:
          emit sig_restart_game();
          break;
        default:
          QGraphicsScene::keyPressEvent(e);
      }
    }


    void game_over::load()
    {
      QFont f;
      f.setPixelSize(20);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Paint the background in black.
      QGraphicsRectItem* r = new QGraphicsRectItem(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);
      r->setBrush(brush);
      addItem(r);

      //Draw GAME OVER in the center of the view.
      QGraphicsTextItem* text = new QGraphicsTextItem();
      text->setHtml("<center>GAME OVER</center>");
      text->setFont(f);
      text->setPos(0, AMD_SCENE_HEIGHT / 2);
      text->setTextWidth(AMD_SCENE_WIDTH);
      text->setDefaultTextColor(QColor(Qt::white));
      addItem(text);
    }

  } // namespace scene

} // namespace game
