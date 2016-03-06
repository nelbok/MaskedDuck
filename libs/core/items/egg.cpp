#include "egg.hpp"

namespace core
{
  
  egg::egg(int id, const QPoint& pos, const type_egg& t, int width, int height)
    : core::block(get_img(t), pos, width, height)
  {
    setData(Qt::UserRole, id);
  }


  const QString egg::get_img(const type_egg& t) const
  {
    switch (t)
    {
      case EGG:     return QString(":/core/egg.png");
      case NO_EGG:  return QString(":/core/no_egg.png");
      case NEW_EGG: return QString(":/core/new_egg.png");
    }

    Q_ASSERT(false);
    return QString("");
  }

} // namespace core
