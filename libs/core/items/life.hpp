#ifndef CORE_ITEMS_LIFE_HPP
# define CORE_ITEMS_LIFE_HPP

# include "core/items/block.hpp"

namespace core
{
  
  /*! Type of the egg. */
  enum type_life
  {
    LIFE,      /*!< Draw a life.*/
    NO_LIFE,   /*!< Draw a empty life.*/
    NEW_LIFE   /*!< Draw a life with a halo.*/
  };

  /*!
   *  Life block.\n
   * \param id The identifying of the life.
   * \param t The type of the life.
   */

  class life : public core::block
  {
    public:
      life(int id, const QPoint& pos, const type_life& t = LIFE, int width = 0, int height = 0);

    private:
      const QString get_img(const type_life& t) const;
  };
  
} // namespace core

#endif // CORE_ITEMS_LIFE_HPP
