#include <QDir>
#include <QLibrary>
#include <QCoreApplication>

#include "core/map.hpp"

namespace core
{

  map::map()
  {
    load_worlds();
  }

  map::~map()
  {
  }


  const QList<world_ptr>& map::worlds() const
  {
    Q_ASSERT(not worlds_.isEmpty());
    return worlds_;
  }

  void map::load_worlds()
  {
    worlds_.clear();

    // Get the maps directory
    QDir d(QString("%1/maps/").arg(QCoreApplication::applicationDirPath()));
    // Get all the files which have the extension which ends by: .dll, .so and .dylib
    QStringList list = d.entryList(QStringList() << "*.dll" << "*.so" << "*.dylib", QDir::Files, QDir::Name);

    for (int i = 0; i < list.size(); ++i)
      load_world(list.at(i));
  }

  void map::load_world(const QString& name)
  {
    // Get the filepath of the file
    QString file_path = QString("%1/maps/%2").arg(QCoreApplication::applicationDirPath()).arg(name);

    // Verify that the file is a library
    if (not QLibrary::isLibrary(file_path))
      return;

    QLibrary lib(file_path);

    typedef core::world* (*load)();

    // Get the function to load the world in the library file
    load foo = (load) lib.resolve("load");
    Q_ASSERT_X(foo, "load_world", qPrintable(QString("Load error: %1").arg(name)));

    // Add the new world to the list
    world_ptr w = world_ptr(foo());
    worlds_.append(w);
  }

} // namespace core
