#include "core/world_item.hpp"

namespace core
{
  
  world_item::world_item(const QPoint& pos, boss_ptr data)
    : pos_(pos)
    , type_(world_item::BOSS)
    , boss_(data)
    , stage_(data)
  {
  }

  world_item::world_item(const QPoint& pos, level_ptr data)
    : pos_(pos)
    , type_(world_item::LEVEL)
    , level_(data)
    , stage_(data)
  {
  }

  world_item::world_item(const QPoint& pos, pnj_ptr data)
    : pos_(pos)
    , type_(world_item::PNJ)
    , pnj_(data)
    , stage_(data)
  {
  }

  world_item::world_item(const QPoint& pos, bool return_type)
    : pos_(pos)
    , type_((return_type) ? world_item::RETURN : world_item::NONE)
  {
  }

  world_item::~world_item()
  {
  }


  const QPoint& world_item::pos() const
  {
    return pos_;
  }

  world_item::item_type world_item::type() const
  {
    return type_;
  }


  void world_item::pos(const QPoint& p)
  {
    pos_ = p;
  }

  void world_item::type(world_item::item_type t)
  {
    type_ = t;
  }


  bool world_item::is_boss() const
  {
    return boss_;
  }

  bool world_item::is_level() const
  {
    return level_;
  }

  bool world_item::is_pnj() const
  {
    return pnj_;
  }

  bool world_item::is_stage() const
  {
    return stage_;
  }


  boss_ptr world_item::boss() const
  {
    Q_ASSERT(boss_);
    return boss_;
  }

  level_ptr world_item::level() const
  {
    Q_ASSERT(level_);
    return level_;
  }

  pnj_ptr world_item::pnj() const
  {
    Q_ASSERT(pnj_);
    return pnj_;
  }

  stage_ptr world_item::stage() const
  {
    Q_ASSERT(stage_);
    return stage_;
  }


  void world_item::add_connexion(world_item_ptr w1, world_item_ptr w2, int id_door)
  {
    Q_ASSERT(w1 != w2);
    Q_ASSERT(not w1->contains_connexion(w2) and not w2->contains_connexion(w1));
    w1->connexions_.insert(w2, id_door);
    w2->connexions_.insert(w1, id_door);
  }

  void world_item::modify_connexion(world_item_ptr w1, world_item_ptr w2, int id_door)
  {
    Q_ASSERT(w1 != w2);
    Q_ASSERT(w1->contains_connexion(w2) and w2->contains_connexion(w1));
    w1->connexions_[w2] = id_door;
    w2->connexions_[w1] = id_door;
  }

  void world_item::remove_connexion(world_item_ptr w1, world_item_ptr w2)
  {
    Q_ASSERT(w1 != w2);
    Q_ASSERT(w1->contains_connexion(w2) and w2->contains_connexion(w1));
    w1->connexions_.remove(w2);
    w2->connexions_.remove(w1);
  }

  void world_item::clear_connexions(world_item_ptr w1)
  {
    QMapIterator<world_item_ptr, int> i(w1->connexions_);
    while (i.hasNext())
    {
      i.next();
      world_item_ptr w2 = i.key();
      w2->connexions_.remove(w1);
    }
    w1->connexions_.clear();
  }

  bool world_item::contains_connexion(world_item_ptr item) const
  {
    Q_ASSERT(this != item.data());
    return connexions_.contains(item);
  }

  const QMap<world_item_ptr, int>& world_item::connexions() const
  {
    return connexions_;
  }

} // namespace core
