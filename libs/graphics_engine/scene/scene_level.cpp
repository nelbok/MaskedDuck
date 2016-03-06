#include "core/items/block.hpp"

#include "graphics_engine/scene/scene_level.hpp"
#include "graphics_engine/constant.hpp"

namespace graphics_engine
{
  
  scene_level::scene_level(QObject* parent)
    : QGraphicsScene(parent)
    , backitem_(0)
    , decoitem_(0)
    , signitem_(0)
    , dooritem_(0)
    , lifeitem_(0)
    , eggsitem_(0)
    , baseitem_(0)
    , foreitem_(0)
    , deaditem_(0)
  {
  }
  

  void scene_level::reload(level_ptr l, const QList<bool>& acquired_eggs, const QList<bool>& acquired_lifes)
  {
    clear();
    setSceneRect(0, 0, AMD_SCENE_WIDTH, AMD_SCENE_HEIGHT);

    backitem_ = draw_items(l->background(), AMD_BACK_DEPTH);
    decoitem_ = draw_items(l->decor(), AMD_DECO_DEPTH);
    signitem_ = draw_items(l->signs(), AMD_SIGN_DEPTH);
    dooritem_ = draw_items(l->doors(), AMD_DOOR_DEPTH);
    lifeitem_ = draw_items(l->lifes(acquired_lifes), AMD_BASE_DEPTH);
    eggsitem_ = draw_items(l->eggs(acquired_eggs), AMD_BASE_DEPTH);
    baseitem_ = draw_items(l->baseground(), AMD_BASE_DEPTH);
    foreitem_ = draw_items(l->foreground(), AMD_FORE_DEPTH);
    deaditem_ = draw_items(l->death_items(), AMD_FORE_DEPTH);
  }

  void scene_level::move_background(int dx, int dy)
  {
    move_background(backitem_->pos() + QPointF(dx, dy));
  }

  void scene_level::move_background(const QPointF& pos)
  {
    backitem_->setPos(pos);
  }


  QGraphicsItemGroup* scene_level::draw_items(const QList<core::block*>& l, int depth)
  {
    // Create group
    QGraphicsItemGroup* group = new QGraphicsItemGroup();
    group->setPos(0, 0);
    group->setZValue(depth);
    addItem(group);

    // Add item
    for (int i = 0; i < l.size(); ++i)
      group->addToGroup(l.at(i));

    return group;
  }

} // namespace graphics_engine
