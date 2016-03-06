#include <QSettings>

#include "game/data/player.hpp"
#include "game/constant.hpp"

namespace game
{

  namespace data
  {

    player::player(int id)
      : map_(map_ptr(new core::map))
      , id_(id)
      , lifes_(AMD_NB_LIFES)
      , new_game_(true)
    {
      // Init the worlds list with the map param.
      const QList<world_ptr>& list = map_->worlds();
      for (int i = 0; i < list.size(); ++i)
      {
        world_ptr w = list.at(i);
        game_world_ptr dw = game_world_ptr(new data::world(w));
        worlds_.insert(w->id(), dw);
      }

      load();
    }

    player::~player()
    {
    }


    map_ptr player::map() const
    {
      return map_;
    }

    world_ptr player::current_world() const
    {
      return current_world_;
    }

    world_item_ptr player::current_world_item() const
    {
      return current_world_item_;
    }


    void player::current_world(world_ptr w)
    {
      current_world_ = w;
    }

    void player::current_world_item(world_item_ptr wi)
    {
      current_world_item_ = wi;
    }


    int player::id() const
    {
      return id_;
    }


    void player::add_life()
    {
      ++lifes_;
    }

    void player::remove_life()
    {
      --lifes_;
    }

    int player::lifes() const
    {
      return lifes_;
    }


    bool player::open_door(level_ptr l, int id_door) const
    {
      Q_ASSERT(current_world_);
      return worlds_.value(current_world_->id())->open_door(l->id(), id_door);
    }

    void player::open_door(level_ptr l, int id_door, bool open)
    {
      Q_ASSERT(current_world_);
      worlds_[current_world_->id()]->open_door(l->id(), id_door, open);
    }


    const QList<bool>& player::acquired_eggs() const
    {
      Q_ASSERT(current_world_);
      Q_ASSERT(current_world_item_);
      return worlds_.value(current_world_->id())->acquired_eggs(current_world_item_->level()->id());
    }

    void player::acquired_egg(int id_egg)
    {
      Q_ASSERT(current_world_);
      Q_ASSERT(current_world_item_);
      worlds_[current_world_->id()]->acquired_egg(current_world_item_->level()->id(), id_egg);
    }

    int player::nb_acquired_eggs(int id_world) const
    {
      Q_ASSERT(worlds_.contains(id_world));
      return worlds_.value(id_world)->nb_acquired_eggs();
    }

    int player::nb_acquired_eggs() const
    {
      int nb = 0;

      QMapIterator<int, game_world_ptr> i(worlds_);
      while (i.hasNext())
      {
        i.next();
        nb += i.value()->nb_acquired_eggs();
      }

      return nb;
    }

    int player::max_eggs(int id_world) const
    {
      Q_ASSERT(worlds_.contains(id_world));
      return worlds_.value(id_world)->max_eggs();
    }

    int player::max_eggs() const
    {
      int max = 0;

      QMapIterator<int, game_world_ptr> i(worlds_);
      while (i.hasNext())
      {
        i.next();
        max += i.value()->max_eggs();
      }

      return max;
    }


    const QList<bool>& player::acquired_lifes() const
    {
      Q_ASSERT(current_world_);
      Q_ASSERT(current_world_item_);
      return worlds_.value(current_world_->id())->acquired_lifes(current_world_item_->level()->id());
    }

    void player::acquired_life(int id_life)
    {
      Q_ASSERT(current_world_);
      Q_ASSERT(current_world_item_);
      worlds_[current_world_->id()]->acquired_life(current_world_item_->level()->id(), id_life);
    }

    int player::nb_acquired_lifes(int id_world) const
    {
      Q_ASSERT(worlds_.contains(id_world));
      return worlds_.value(id_world)->nb_acquired_lifes();
    }

    int player::max_lifes(int id_world) const
    {
      Q_ASSERT(worlds_.contains(id_world));
      return worlds_.value(id_world)->max_lifes();
    }


    QString player::save_dir()
    {
      QSettings s (QSettings::IniFormat, QSettings::UserScope, QString("ShadowRevival"), QString("MaskedDuck"));
      return s.fileName();
    }

    void player::save()
    {
      QSettings s (QSettings::IniFormat, QSettings::UserScope, QString("ShadowRevival"), QString("MaskedDuck"));

      s.beginGroup(QString::number(id()));

      int encrypted_life = lifes_ ^ AMD_MAGIC_CRYPT;
      s.setValue("data", QVariant(encrypted_life));

      // Save world
      QMapIterator<int, game_world_ptr> i(worlds_);
      while (i.hasNext())
      {
        i.next();
        int id = i.key();
        game_world_ptr dw = i.value();
        s.beginGroup(QString::number(id));
        dw->save(s);
        s.endGroup();
      }

      s.endGroup();

      new_game_ = false;
    }

    void player::reset()
    {
      QSettings s (QSettings::IniFormat, QSettings::UserScope, QString("ShadowRevival"), QString("MaskedDuck"));

      s.beginGroup(QString::number(id()));
      lifes_ = AMD_NB_LIFES;

      // Reset world
      QMapIterator<int, game_world_ptr> i(worlds_);
      while (i.hasNext())
      {
        i.next();
        int id = i.key();
        game_world_ptr dw = i.value();
        s.beginGroup(QString::number(id));
        dw->reset(s);
        s.endGroup();
      }

      s.remove("");
      s.endGroup();

      new_game_ = true;
    }

    void player::load()
    {
      QSettings s (QSettings::IniFormat, QSettings::UserScope, QString("ShadowRevival"), QString("MaskedDuck"));

      s.beginGroup(QString::number(id()));

      // FIXME: Secure
      if (not s.contains("data"))
        return;

      int encrypted_life = s.value("data").toInt();
      lifes_ = encrypted_life ^ AMD_MAGIC_CRYPT;

      // Load world
      QMapIterator<int, game_world_ptr> i(worlds_);
      while (i.hasNext())
      {
        i.next();
        int id = i.key();
        game_world_ptr dw = i.value();
        s.beginGroup(QString::number(id));
        dw->load(s);
        s.endGroup();
      }

      s.endGroup();

      new_game_ = false;
    }

    bool player::new_game() const
    {
      return new_game_;
    }

  } // namespace data

} // namespace game
