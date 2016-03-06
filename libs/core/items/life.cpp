#include "life.hpp"

namespace core
{
  
  life::life(int id, const QPoint& pos, const type_life& t, int width, int height)
    : core::block(get_img(t), pos, width, height)
  {
    setData(Qt::UserRole, QVariant(id));
  }


  const QString life::get_img(const type_life& t) const
  {
    switch (t)
    {
      case LIFE:     return QString(":/core/life.png");
      case NO_LIFE:  return QString(":/core/no_life.png");
      case NEW_LIFE: return QString(":/core/new_life.png");
    }

    Q_ASSERT(false);
    return QString("");
  }

} // namespace core
