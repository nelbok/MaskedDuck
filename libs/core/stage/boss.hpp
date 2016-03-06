#ifndef CORE_STAGE_BOSS_HPP
# define CORE_STAGE_BOSS_HPP

# include "core/stage.hpp"

namespace core
{

  /*!
   *  Class abstracted from a boss stage.
   */

  class boss : public core::stage
  {
    public:
      boss() {}
      virtual ~boss() {}
  };

} // namespace core

typedef QSharedPointer<core::boss> boss_ptr;

#endif // CORE_STAGE_BOSS_HPP
