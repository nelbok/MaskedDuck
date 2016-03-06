#include <QKeyEvent>
#include <QGraphicsItem>

#include "game/items/status_game.hpp"
#include "game/scene/scene_menu.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace scene
  {

    scene_menu::scene_menu()
      : current_(0)
    {
      load();
    }


    void scene_menu::keyPressEvent(QKeyEvent* e)
    {
      if (e->isAutoRepeat())
        return;

      switch (e->key())
      {
        case Qt::Key_Left:
        case Qt::Key_Right:
          current_->change_option();
          break;
        case Qt::Key_Up:
        {
          // Change the selection of the game
          int index = infos_game_.indexOf(current_);
          --index;
          if (index < 0)
            index = infos_game_.size() - 1;
          update_info_game(index);
          break;
        }
        case Qt::Key_Down:
        {
          // Change the selection of the game
          int index = infos_game_.indexOf(current_);
          ++index;
          if (index >= infos_game_.size())
            index = 0;
          update_info_game(index);
          break;
        }
        case Qt::Key_Escape:
          emit sig_escape_pushed();
          break;
        case Qt::Key_Return:
          if (not current_->reset_mode())
            emit sig_game_selected(current_->player());
          else
            reset_info_game();
          break;
        default:
          QGraphicsScene::keyPressEvent(e);
      }
    }


    void scene_menu::load()
    {
      clear();
      setSceneRect(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);
      infos_game_.clear();

      // Draw scene
      draw_background(AMD_BACK_DEPTH);
      draw_info_top(AMD_INFO_DEPTH);
      draw_info_game(AMD_BASE_DEPTH);
      draw_info_save_dir(AMD_INFO_DEPTH);
    }


    void scene_menu::draw_background(int depth)
    {
      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(QColor("#7b4524"));
      QGraphicsRectItem* r = new QGraphicsRectItem(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);
      r->setZValue(depth);
      r->setBrush(brush);
      addItem(r);
    }

    void scene_menu::draw_info_top(int depth)
    {
      QFont f;
      f.setPixelSize(30);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Draw rect
      QGraphicsRectItem* r = new QGraphicsRectItem(0, 0, AMD_SCENE_WIDTH, 50);
      r->setBrush(brush);
      r->setZValue(depth);
      addItem(r);

      // Draw text
      QGraphicsTextItem* text = new QGraphicsTextItem();
      text->setHtml(QString("<center>Select a game</center>"));
      text->setFont(f);
      text->setPos(0, 0);
      text->setTextWidth(AMD_SCENE_WIDTH);
      text->setDefaultTextColor(QColor(Qt::white));
      text->setZValue(depth);
      addItem(text);
    }

    void scene_menu::draw_info_game(int depth)
    {
      for (int i = 0; i < 3; ++i)
      {
        game_player_ptr p = game_player_ptr(new data::player(i + 1));
        items::status_game* item = new items::status_game(p);
        if (not current_)
        {
          current_ = item;
          item->focus();
        }
        item->setZValue(depth);
        item->setPos(0, 50 + i * 170);
        addItem(item);
        infos_game_.append(item);
      }
    }

    void scene_menu::draw_info_save_dir(int depth)
    {
      QFont f;
      f.setPixelSize(12);

      QBrush brush;
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::black);

      // Draw rect
      QGraphicsRectItem* r = new QGraphicsRectItem(0, 570, AMD_SCENE_WIDTH, 30);
      r->setBrush(brush);
      r->setZValue(depth);
      addItem(r);

      // Draw text
      QGraphicsTextItem* text = new QGraphicsTextItem();
      text->setHtml(QString("<center>Save filename: %1</center>").arg(data::player::save_dir()));
      text->setFont(f);
      text->setPos(0, 575);
      text->setTextWidth(AMD_SCENE_WIDTH);
      text->setDefaultTextColor(QColor(Qt::white));
      text->setZValue(depth);
      addItem(text);
    }


    void scene_menu::reset_info_game()
    {
      current_->player()->reset();
      current_->reinit();
    }

    void scene_menu::update_info_game(int index)
    {
      for (int i = 0; i < infos_game_.size(); ++i)
        infos_game_.at(i)->unfocus();

      current_ = infos_game_.at(index);
      current_->focus();
    }

  } // namespace scene

} // namespace game
