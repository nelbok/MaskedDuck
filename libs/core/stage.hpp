#ifndef CORE_STAGE_HPP
# define CORE_STAGE_HPP

# include "core/no_copy.hpp"

namespace core
{
  
  /*!
   *  Class abstracted from a stage.
   * \sa stage::level, stage::boss and stage::pnj
   */

  class stage : public no_copy
  {
    public:
      stage() {}
      virtual ~stage() {}

      virtual int id() const = 0;
      virtual const QString name() const = 0;

  };
  
} // namespace core

typedef QSharedPointer<core::stage> stage_ptr;

#endif // CORE_STAGE_HPP
