#ifndef CORE_NO_COPY_HPP
# define CORE_NO_COPY_HPP

# include <QSharedPointer>

namespace core
{

  /*!
   *  This class doesn't allow to create or clone a instance of this.
   */

  class no_copy
  {
    public:
      no_copy() {}
      virtual ~no_copy() {}

    private:
      no_copy(no_copy const &);
      no_copy& operator=(no_copy const &);
  };

} // namespace core

typedef QSharedPointer<core::no_copy> no_copy_ptr;

#endif // CORE_NO_COPY_HPP
