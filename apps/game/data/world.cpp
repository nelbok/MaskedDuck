#include <QSettings>

#include "game/data/world.hpp"

namespace game
{

  namespace data
  {


    world::world(world_ptr w)
    {
      // Init the levels list with the world param.
      const QList<world_item_ptr>& list = w->world_items();
      for (int i = 0; i < list.size(); ++i)
        if (list.at(i)->is_level())
          if (level_ptr l = list.at(i)->level())
          {
            game_level_ptr dl = game_level_ptr(new data::level(l));
            levels_.insert(l->id(), dl);
          }
    }

    world::~world()
    {
    }


    bool world::open_door(int id_level, int id_door) const
    {
      Q_ASSERT(levels_.contains(id_level));
      return levels_.value(id_level)->open_door(id_door);
    }

    void world::open_door(int id_level, int id_door, bool open)
    {
      Q_ASSERT(levels_.contains(id_level));
      levels_[id_level]->open_door(id_door, open);
    }


    const QList<bool>& world::acquired_eggs(int id_level) const
    {
      Q_ASSERT(levels_.contains(id_level));
      return levels_.value(id_level)->acquired_eggs();
    }

    void world::acquired_egg(int id_level, int id_egg)
    {
      Q_ASSERT(levels_.contains(id_level));
      levels_[id_level]->acquired_egg(id_egg);
    }

    int world::nb_acquired_eggs() const
    {
      int nb = 0;

      QMapIterator<int, game_level_ptr> i(levels_);
      while (i.hasNext())
      {
        i.next();
        nb += i.value()->nb_acquired_eggs();
      }

      return nb;
    }

    int world::max_eggs() const
    {
      int max = 0;

      QMapIterator<int, game_level_ptr> i(levels_);
      while (i.hasNext())
      {
        i.next();
        max += i.value()->max_eggs();
      }

      return max;
    }


    const QList<bool>& world::acquired_lifes(int id_level) const
    {
      Q_ASSERT(levels_.contains(id_level));
      return levels_.value(id_level)->acquired_lifes();
    }

    void world::acquired_life(int id_level, int id_life)
    {
      Q_ASSERT(levels_.contains(id_level));
      levels_[id_level]->acquired_life(id_life);
    }

    int world::nb_acquired_lifes() const
    {
      int nb = 0;

      QMapIterator<int, game_level_ptr> i(levels_);
      while (i.hasNext())
      {
        i.next();
        nb += i.value()->nb_acquired_lifes();
      }

      return nb;
    }

    int world::max_lifes() const
    {
      int max = 0;

      QMapIterator<int, game_level_ptr> i(levels_);
      while (i.hasNext())
      {
        i.next();
        max += i.value()->max_lifes();
      }

      return max;
    }


    void world::save(QSettings& s)
    {
      QMapIterator<int, game_level_ptr> i(levels_);
      while (i.hasNext())
      {
        i.next();
        int id = i.key();
        game_level_ptr dl = i.value();
        s.beginGroup(QString::number(id));
        dl->save(s);
        s.endGroup();
      }
    }

    void world::reset(QSettings& s)
    {
      QMapIterator<int, game_level_ptr> i(levels_);
      while (i.hasNext())
      {
        i.next();
        int id = i.key();
        game_level_ptr dl = i.value();
        s.beginGroup(QString::number(id));
        dl->reset(s);
        s.endGroup();
      }
      s.remove("");
    }

    void world::load(QSettings& s)
    {
      QMapIterator<int, game_level_ptr> i(levels_);
      while (i.hasNext())
      {
        i.next();
        int id = i.key();
        game_level_ptr dl = i.value();
        s.beginGroup(QString::number(id));
        dl->load(s);
        s.endGroup();
      }
    }

  } // namespace data

} // namespace game
