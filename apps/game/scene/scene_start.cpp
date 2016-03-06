#include <QKeyEvent>
#include <QGraphicsItem>

#include "game/scene/scene_start.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace scene
  {

    scene_start::scene_start()
    {
      load();
    }


    void scene_start::keyPressEvent(QKeyEvent* e)
    {
      if (e->isAutoRepeat())
        return;

      switch (e->key())
      {
        case Qt::Key_Return:
          emit sig_return_pushed();
          break;
        case Qt::Key_Escape:
          emit sig_escape_pushed();
          break;
        default:
          QGraphicsScene::keyPressEvent(e);
      }
    }

    void scene_start::load()
    {
      clear();
      setSceneRect(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);

      QFont f;

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Draw background
      QGraphicsRectItem* r = new QGraphicsRectItem(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);
      r->setBrush(brush);
      addItem(r);

      // Draw title
      QGraphicsTextItem* title = new QGraphicsTextItem();
      f.setPixelSize(40);
      title->setFont(f);
      title->setPos(0, 50);
      title->setTextWidth(AMD_SCENE_WIDTH);
      title->setDefaultTextColor(QColor(Qt::white));
      title->setHtml("<center>"AMD_NAME"</center>");
      addItem(title);

      // Draw pixmap
      QGraphicsPixmapItem* main = new QGraphicsPixmapItem(QPixmap(":/game/main.png"));
      main->setPos(0, AMD_SCENE_HEIGHT / 4);
      addItem(main);


      // Draw body
      QGraphicsTextItem* body = new QGraphicsTextItem();
      f.setPixelSize(12);
      body->setFont(f);
      body->setPos(0, AMD_SCENE_HEIGHT * 2 / 3);
      body->setTextWidth(AMD_SCENE_WIDTH);
      body->setDefaultTextColor(QColor(Qt::white));
      body->setHtml("<center>Push Enter to start the game<br/><br/>Push Escape to quit the game</center>");
      addItem(body);

      // Draw bottom
      QGraphicsTextItem* bottom = new QGraphicsTextItem();
      f.setPixelSize(12);
      bottom->setFont(f);
      bottom->setPos(0, AMD_SCENE_HEIGHT - 50);
      bottom->setTextWidth(AMD_SCENE_WIDTH);
      bottom->setDefaultTextColor(QColor(Qt::white));
      bottom->setHtml("<center>2012 (c) Shadow Revival</center>");
      addItem(bottom);
    }

  } // namespace scene

} // namespace game
