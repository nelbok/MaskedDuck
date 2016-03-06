#ifndef WORLD2_HPP
# define WORLD2_HPP

# ifdef Q_WS_WIN
#  define MY_EXPORT __declspec(dllexport)
# else
#  define MY_EXPORT
# endif

# include "core/world.hpp"

namespace world2
{

  class world2 : public core::world
  {
    public:
      world2();

      virtual int id() const;
      virtual const QString name() const;
      virtual const QPixmap pixmap() const;
      virtual const QPoint pos() const;
      virtual const QPoint global_pos() const;

  };

  extern "C" MY_EXPORT core::world* load()
  {
    return new world2;
  }

} // namespace world2

#endif // WORLD2_HPP
