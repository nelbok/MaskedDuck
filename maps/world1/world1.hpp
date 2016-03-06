#ifndef WORLD1_HPP
# define WORLD1_HPP

# ifdef Q_WS_WIN
#  define MY_EXPORT __declspec(dllexport)
# else
#  define MY_EXPORT
# endif

# include "core/world.hpp"

namespace world1
{

  class world1 : public core::world
  {
    public:
      world1();

      virtual int id() const;
      virtual const QString name() const;
      virtual const QPixmap pixmap() const;
      virtual const QPoint pos() const;
      virtual const QPoint global_pos() const;

  };

  extern "C" MY_EXPORT core::world* load()
  {
    return new world1;
  }

} // namespace world1

#endif // WORLD1_HPP
