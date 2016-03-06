#ifndef WORLD0_HPP
# define WORLD0_HPP

# ifdef Q_WS_WIN
#  define MY_EXPORT __declspec(dllexport)
# else
#  define MY_EXPORT
# endif

# include "core/world.hpp"

namespace world0
{

  class world0 : public core::world
  {
    public:
      world0();

      virtual int id() const;
      virtual const QString name() const;
      virtual const QPixmap pixmap() const;
      virtual const QPoint pos() const;
      virtual const QPoint global_pos() const;

  };

  extern "C" MY_EXPORT core::world* load()
  {
    return new world0;
  }

} // namespace world0

#endif // WORLD0_HPP
