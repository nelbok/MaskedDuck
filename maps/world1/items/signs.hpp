#ifndef WORLD1_ITEMS_SIGNS_HPP
# define WORLD1_ITEMS_SIGNS_HPP

# include "core/items/block.hpp"

namespace world1
{

  //Information

  class sign_danger : public core::block
  {
    public:
      sign_danger(const QPoint pos);
  };

  class sign_get : public core::block
  {
    public:
      sign_get(const QPoint pos);
  };

  class sign_jump : public core::block
  {
    public:
      sign_jump(const QPoint pos);
  };

  class sign_move : public core::block
  {
    public:
      sign_move(const QPoint pos);
  };

  class sign_open : public core::block
  {
    public:
      sign_open(const QPoint pos);
  };


  //Direction

  class sign_up : public core::block
  {
    public:
      sign_up(const QPoint pos);
  };

  class sign_up_left : public core::block
  {
    public:
      sign_up_left(const QPoint pos);
  };

  class sign_up_right : public core::block
  {
    public:
      sign_up_right(const QPoint pos);
  };

  class sign_left : public core::block
  {
    public:
      sign_left(const QPoint pos);
  };

  class sign_right : public core::block
  {
    public:
      sign_right(const QPoint pos);
  };

  class sign_down : public core::block
  {
    public:
      sign_down(const QPoint pos);
  };

  class sign_down_left : public core::block
  {
    public:
      sign_down_left(const QPoint pos);
  };

  class sign_down_right : public core::block
  {
    public:
      sign_down_right(const QPoint pos);
  };

} // namespace world1

#endif // WORLD1_ITEMS_SIGNS_HPP
