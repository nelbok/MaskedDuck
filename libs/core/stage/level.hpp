#ifndef CORE_STAGE_LEVEL_HPP
# define CORE_STAGE_LEVEL_HPP

# include <QList>

# include "core/stage.hpp"

class QPoint;

namespace core
{
  class block;

    /*!
     *  Class abstracted from a level stage. \n
     *  Contains a list of elements for every layer of display.
     */

  class level : public core::stage
  {
    public:
      level() {}
      virtual ~level() {}

      /*! Starting position of the duck. */
      virtual const QPoint start_position() const = 0;
      /*! First layer of display. */
      virtual const QList<core::block*> background() const = 0;
      /*! Second layer of display. */
      virtual const QList<core::block*> decor() const = 0;
      /*! Second layer of display. */
      virtual const QList<core::block*> signs() const = 0;
      /*! Second layer of display. */
      virtual const QList<core::block*> doors() const = 0;
      /*! Second layer of display.
       * \param already_acquired List of eggs that the player has already obtained in the level stage.
       */
      virtual const QList<core::block*> eggs(const QList<bool>& already_acquired) const = 0;
      /*! Second layer of display.
       * \param already_acquired List of lifes that the player has already obtained in the level stage.
       */
      virtual const QList<core::block*> lifes(const QList<bool>& already_acquired) const = 0;
      /*! Third layer of display. */
      virtual const QList<core::block*> baseground() const = 0;
      /*! Last layer of display. */
      virtual const QList<core::block*> foreground() const = 0;
      /*! Last layer of display. */
      virtual const QList<core::block*> death_items() const = 0;
  };

} // namespace core

typedef QSharedPointer<core::level> level_ptr;

#endif // CORE_STAGE_LEVEL_HPP
