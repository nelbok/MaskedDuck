#include "signs.hpp"

namespace world1
{

  //Information

  sign_danger::sign_danger(const QPoint pos)
    : core::block(":/world1/info/danger.png", pos)
  {
  }

  sign_get::sign_get(const QPoint pos)
    : core::block(":/world1/info/get.png", pos)
  {
  }

  sign_jump::sign_jump(const QPoint pos)
    : core::block(":/world1/info/jump.png", pos)
  {
  }

  sign_move::sign_move(const QPoint pos)
    : core::block(":/world1/info/move.png", pos)
  {
  }

  sign_open::sign_open(const QPoint pos)
    : core::block(":/world1/info/open.png", pos)
  {
  }


  //Direction

  sign_up::sign_up(const QPoint pos)
    : core::block(":/world1/direction/up.png", pos)
  {
  }

  sign_up_left::sign_up_left(const QPoint pos)
    : core::block(":/world1/direction/up_right.png", pos)
  {
    setTransform(QTransform::fromScale(-1, 1), true);
  }

  sign_up_right::sign_up_right(const QPoint pos)
    : core::block(":/world1/direction/up_right.png", pos)
  {
  }

  sign_left::sign_left(const QPoint pos)
    : core::block(":/world1/direction/right.png", pos)
  {
    setTransform(QTransform::fromScale(-1, 1), true);
  }

  sign_right::sign_right(const QPoint pos)
    : core::block(":/world1/direction/right.png", pos)
  {
  }

  sign_down::sign_down(const QPoint pos)
    : core::block(":/world1/direction/down.png", pos)
  {
  }

  sign_down_left::sign_down_left(const QPoint pos)
    : core::block(":/world1/direction/down_right.png", pos)
  {
    setTransform(QTransform::fromScale(-1, 1), true);
  }

  sign_down_right::sign_down_right(const QPoint pos)
    : core::block(":/world1/direction/down_right.png", pos)
  {
  }

} // namespace world1
