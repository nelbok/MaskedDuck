#ifndef CORE_ITEMS_EGG_HPP
# define CORE_ITEMS_EGG_HPP

# include "core/items/block.hpp"

namespace core
{
  
  /*! Type of the egg. */
  enum type_egg
  {
    EGG,      /*!< Draw a egg.*/
    NO_EGG,   /*!< Draw a empty egg.*/
    NEW_EGG   /*!< Draw a egg with a halo.*/
  };

  /*!
   *  Egg block.\n
   * \param id The identifying of the egg.
   * \param t The type of the egg.
   */

  class egg : public core::block
  {
    public:
      egg(int id, const QPoint& pos, const type_egg& t = EGG, int width = 0, int height = 0);

    private:
      const QString get_img(const type_egg& t) const;
  };
  
} // namespace core

#endif // CORE_ITEMS_EGG_HPP
