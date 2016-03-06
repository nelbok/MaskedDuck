#ifndef CORE_STAGE_PNJ_HPP
# define CORE_STAGE_PNJ_HPP

# include "core/stage.hpp"

namespace core
{
  
  /*!
   *  Class abstracted from a pnj stage.
   */

  class pnj : public core::stage
  {
    public:
      pnj() {}
      virtual ~pnj() {}
  };
  
} // namespace core

typedef QSharedPointer<core::pnj> pnj_ptr;

#endif // CORE_STAGE_PNJ_HPP
