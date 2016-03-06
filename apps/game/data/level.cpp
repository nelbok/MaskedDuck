#include <QMetaType>
#include <QSettings>

#include "game/data/level.hpp"

/*! Class for the management of the saving. */
typedef QList<bool> dOOb;

Q_DECLARE_METATYPE(dOOb)

/*! Methods for the management of the saving. */
QDataStream &operator<<(QDataStream &out, const dOOb& l)
{
  int size = l.size();
  out << QByteArray::number(size);

  for (int i = 0; i < size; ++i)
    out << QByteArray::number(l.at(i));

  return out;
}

/*! Methods for the management of the saving. */
QDataStream &operator>>(QDataStream &in, dOOb& l)
{
  QByteArray tmp;

  in >> tmp;
  int size = tmp.toInt();

  for (int i = 0; i < size; ++i)
  {
    in >> tmp;
    l.append(tmp.toInt());
  }

  return in;
}

namespace game
{

  namespace data
  {

    level::level(level_ptr l)
    {
      // Init the dOOb class
      qRegisterMetaTypeStreamOperators<dOOb>("dOOb");

      // Init the lists with the level param.
      for (int i = 0; i < l->doors().size(); ++i)
        open_doors_.append(false);
      for (int i = 0; i < l->eggs(QList<bool>()).size(); ++i)
        acquired_eggs_.append(false);
      for (int i = 0; i < l->lifes(QList<bool>()).size(); ++i)
        acquired_lifes_.append(false);
    }

    level::~level()
    {
    }


    bool level::open_door(int id_door) const
    {
      Q_ASSERT(open_doors_.size() >= id_door);
      return open_doors_.at(id_door - 1);
    }

    void level::open_door(int id_door, bool open)
    {
      Q_ASSERT(open_doors_.size() >= id_door);
      open_doors_[id_door - 1] = open;
    }


    const QList<bool>& level::acquired_eggs() const
    {
      return acquired_eggs_;
    }

    void level::acquired_egg(int id_egg)
    {
      Q_ASSERT(acquired_eggs_.size() >= id_egg);
      acquired_eggs_[id_egg - 1] = true;
    }

    int level::nb_acquired_eggs() const
    {
      int nb = 0;

      for (int i = 0; i < acquired_eggs_.size(); ++i)
        if (acquired_eggs_.at(i))
          ++nb;

      return nb;
    }

    int level::max_eggs() const
    {
      return acquired_eggs_.size();
    }


    const QList<bool>& level::acquired_lifes() const
    {
      return acquired_lifes_;
    }

    void level::acquired_life(int id_life)
    {
      Q_ASSERT(acquired_lifes_.size() >= id_life);
      acquired_lifes_[id_life - 1] = true;
    }

    int level::nb_acquired_lifes() const
    {
      int nb = 0;

      for (int i = 0; i < acquired_lifes_.size(); ++i)
        if (acquired_lifes_.at(i))
          ++nb;

      return nb;
    }

    int level::max_lifes() const
    {
      return acquired_lifes_.size();
    }


    void level::save(QSettings& s)
    {
      s.setValue("val1", QVariant::fromValue(open_doors_));
      s.setValue("val2", QVariant::fromValue(acquired_eggs_));
      s.setValue("val3", QVariant::fromValue(acquired_lifes_));
    }

    void level::reset(QSettings& s)
    {
      s.remove("");
      for (int i = 0; i < open_doors_.size(); ++i)
        open_doors_[i] = false;
      for (int i = 0; i < acquired_eggs_.size(); ++i)
        acquired_eggs_[i] = false;
      for (int i = 0; i < acquired_lifes_.size(); ++i)
        acquired_lifes_[i] = false;
    }

    void level::load(QSettings& s)
    {
      open_doors_     = s.value("val1").value<dOOb>();
      acquired_eggs_  = s.value("val2").value<dOOb>();
      acquired_lifes_ = s.value("val3").value<dOOb>();
    }

  } // namespace data

} // namespace game
