#include <QCoreApplication>
#include <QDir>
#include <QSettings>

#include "editor/data/generate.hpp"
#include "editor/data/world.hpp"

namespace editor
{

  namespace data
  {

    //FIXME: Change the value
    world::world()
      : id_(3)
      , name_("Enter a name")
      , pos_(QPoint(0,0))
      , global_pos_(QPoint(0,0))
      , resource_(editor_resource_ptr(new data::resource(*this)))
    {
      // Add return item by default
      core::world::add_world_item(world_item_ptr(new core::world_item(QPoint(25, 25), true)));
    }

    world::~world()
    {
    }


    void world::id(int a)
    {
      id_ = a;

      emit sig_world_updated();
    }

    void world::name(const QString& a)
    {
      name_ = a;

      emit sig_world_updated();
    }

    void world::pos(const QPoint& a)
    {
      pos_ = a;

      emit sig_world_updated();
    }

    void world::global_pos(const QPoint& a)
    {
      global_pos_ = a;

      emit sig_world_updated();
    }


    int world::id() const
    {
      return id_;
    }

    const QString world::name() const
    {
      return name_;
    }

    const QPixmap world::pixmap() const
    {
      QString filename = QString("%1/img/world.png").arg(dir_world());

      if (QFile::exists(filename))
        return QPixmap(filename);

      return QPixmap();
    }

    const QPoint world::pos() const
    {
      return pos_;
    }

    const QPoint world::global_pos() const
    {
      return global_pos_;
    }

    editor_resource_ptr world::resource() const
    {
      return resource_;
    }


    editor_level_ptr world::get_level(world_item_ptr item) const
    {
      Q_ASSERT(levels_.contains(item));
      return levels_.value(item);
    }


    void world::add_world_item(const QPoint& pos)
    {
      world_item_ptr item = world_item_ptr(new core::world_item(clean_position(pos)));
      core::world::add_world_item(item);
      emit sig_world_updated();
    }

    void world::add_world_item(const QPoint& pos, editor_level_ptr l)
    {
      level_ptr core_l = l;
      world_item_ptr item = world_item_ptr(new core::world_item(clean_position(pos), core_l));
      core::world::add_world_item(item);
      levels_.insert(item, l);
      emit sig_world_updated();
    }

    void world::modify_world_item(world_item_ptr item, const QPoint& new_pos)
    {
      Q_ASSERT(item);
      item->pos(clean_position(new_pos));
      emit sig_world_updated();
    }

    void world::modify_world_item(world_item_ptr item, int id, const QString& name)
    {
      Q_ASSERT(item->is_stage());

      //FIXME: Missing pnj/boss
      if (editor_level_ptr l = get_level(item))
      {
        l->id(id);
        l->name(name);
      }
      emit sig_world_updated();
    }

    void world::remove_world_item(world_item_ptr item)
    {
      core::world::remove_world_item(item);
      //FIXME: Missing pnj/boss
      if (levels_.contains(item))
        levels_.remove(item);

      emit sig_world_updated();
    }


    void world::add_world_item_connexion(world_item_ptr w1, world_item_ptr w2, int id_door)
    {
      if (w1->contains_connexion(w2))
        return;
      core::world_item::add_connexion(w1, w2, id_door);
      emit sig_world_updated();
    }

    void world::modify_world_item_connexion(world_item_ptr w1, world_item_ptr w2, int id_door)
    {
      if (not w1->contains_connexion(w2))
        return;
      core::world_item::modify_connexion(w1, w2, id_door);
      emit sig_world_updated();
    }

    void world::remove_world_item_connexion(world_item_ptr w1, world_item_ptr w2)
    {
      if (not w1->contains_connexion(w2))
        return;
      core::world_item::remove_connexion(w1, w2);
      emit sig_world_updated();
    }


    void world::load()
    {
      QString filename = filename_world();

      if (not QFile::exists(filename))
        return;

      clear_world_items();
      //FIXME: Missing pnj/boss
      levels_.clear();

      QSettings s(filename, QSettings::IniFormat);

      s.beginGroup("world");
      id_ = s.value("id").toInt();
      name_ = s.value("name").toString();
      pos_ = s.value("pos").toPoint();
      global_pos_ = s.value("global_pos").toPoint();
      s.endGroup();

      int size = s.beginReadArray("world_items");
      for (int i = 0; i < size; ++i)
      {
        world_item_ptr res;

        s.setArrayIndex(i);

        int id = s.value("id").toInt();
        core::world_item::item_type t = core::world_item::item_type(s.value("type").toInt());
        const QPoint& pos = s.value("pos").toPoint();
        switch (t)
        {
          //FIXME: Missing pnj/boss
          case core::world_item::NONE:    res = world_item_ptr(new core::world_item(pos)); break;
          case core::world_item::RETURN:  res = world_item_ptr(new core::world_item(pos, true)); break;
          case core::world_item::LEVEL:
          {
            editor_level_ptr l = editor_level_ptr(new data::level(*this, id));
            level_ptr core_l = l;
            res = world_item_ptr(new core::world_item(pos, core_l));
            levels_.insert(res, l);
          }
          break;
          case core::world_item::BOSS:    break;
          case core::world_item::PNJ:     break;
        }

        core::world::add_world_item(res);
      }
      s.endArray();

      size = s.beginReadArray("world_item_connexions");
      const QList<world_item_ptr>& items = world_items();
      for (int i = 0; i < size; ++i)
      {
        s.setArrayIndex(i);

        world_item_ptr w1 = items.at(s.value("w1").toInt());
        world_item_ptr w2 = items.at(s.value("w2").toInt());
        int id_door = s.value("id_door").toInt();

        core::world_item::add_connexion(w1, w2, id_door);
      }
      s.endArray();

      // Stages
      for (int i = 0; i < items.size(); ++i)
      {
        world_item_ptr item = items.at(i);
        //FIXME: Missing pnj/boss
        if (editor_level_ptr l = get_level(item))
            l->load(s);
      }

      resource_->load(s);

      emit sig_world_updated();
    }

    void world::save() const
    {
      create_dir_world();
      QString filename = filename_world();
      QSettings s(filename, QSettings::IniFormat);

      s.clear();

      s.beginGroup("world");
      s.setValue("id", QVariant(id_));
      s.setValue("name", QVariant(name_));
      s.setValue("pos", QVariant(pos_));
      s.setValue("global_pos", QVariant(global_pos_));
      s.endGroup();

      // World items
      const QList<world_item_ptr>& items = world_items();
      s.beginWriteArray("world_items");
      for (int i = 0; i < items.size(); ++i)
      {
        world_item_ptr res = items.at(i);

        s.setArrayIndex(i);
        s.setValue("type", QVariant(res->type()));
        s.setValue("pos", QVariant(res->pos()));
        if (res->is_stage())
          s.setValue("id", QVariant(res->stage()->id()));
        else
          s.setValue("id", QVariant(-1));
      }
      s.endArray();

      // World item connexions
      s.beginWriteArray("world_item_connexions");
      QList<world_item_ptr> already_knows;
      int nb_conn = 0;
      for (int i = 0; i < items.size(); ++i)
      {
        world_item_ptr w1 = items.at(i);
        QMapIterator<world_item_ptr, int> j(w1->connexions());
        while (j.hasNext())
        {
          j.next();
          world_item_ptr w2 = j.key();
          if (not already_knows.contains(w2))
          {
            int id_door = j.value();
            s.setArrayIndex(nb_conn);
            s.setValue("w1", QVariant(i));
            s.setValue("w2", QVariant(items.indexOf(w2)));
            s.setValue("id_door", QVariant(id_door));
            ++nb_conn;
          }
        }
        already_knows.append(w1);
      }
      s.endArray();

      // Stages
      for (int i = 0; i < items.size(); ++i)
      {
        world_item_ptr item = items.at(i);
        //FIXME: Missing pnj/boss
        if (editor_level_ptr l = get_level(item))
          l->save(s);
      }

      //Resources
      resource_->save(s);
    }

    void world::generate() const
    {
      generate_world_pro();
      generate_world_hpp();
      generate_world_cpp();
    }


    void world::create_dir_world() const
    {
      QDir d(QCoreApplication::applicationDirPath());
      d.mkdir(QString("editor/"));
      d.mkdir(QString("editor/world%2/").arg(id_));
    }

    QString world::dir_world() const
    {
      return QString("%1/editor/world%2/")
          .arg(QCoreApplication::applicationDirPath())
          .arg(id_);
    }


    QPoint world::clean_position(const QPoint& old_pos) const
    {
      return QPoint((old_pos.x() + 5) / 25 * 25,
                    (old_pos.y() + 5) / 25 * 25);
    }


    QString world::filename_world() const
    {
      return QString("%1/world.srp").arg(dir_world());
    }


    void world::generate_world_pro() const
    {
      const QList<world_item_ptr>& list = world_items();

      create_dir_world();

      data::generate file(QString("%1/world%2.pro").arg(dir_world()).arg(id_));
      file.open(data::generate::PROJECT_FILE);

      file.write(QString("QT              = core gui"));
      file.write(QString(""));
      file.write(QString("contains(QT_MAJOR_VERSION, 5) QT += widgets"));
      file.write(QString(""));
      file.write(QString("TARGET          = world%1").arg(id_));
      file.write(QString("TEMPLATE        = lib"));
      file.write(QString(""));
      file.write(QString("DESTDIR         = ../../bin/maps"));
      file.write(QString("OBJECTS_DIR     = ../../build/maps/world%1/objects").arg(id_));
      file.write(QString("MOC_DIR         = ../../build/maps/world%1/moc").arg(id_));
      file.write(QString("UI_DIR          = ../../build/maps/world%1/ui").arg(id_));
      file.write(QString("RCC_DIR         = ../../build/maps/world%1/rcc").arg(id_));
      file.write(QString("LIBS            = -L../../bin/ -lmdcore"));
      file.write(QString("INCLUDEPATH     = . ../../libs"));
      file.write(QString("QMAKE_RPATHDIR  = ../../bin/"));
      file.write(QString(""));
      file.write(QString("HEADERS         =         \\"));
      file.write(QString("    items/all.hpp         \\"));
      file.write(QString("    items/background.hpp  \\"));
      file.write(QString("    items/baseground.hpp  \\"));
      file.write(QString("    items/decor.hpp       \\"));
      file.write(QString("    items/death_items.hpp \\"));
      file.write(QString("    items/door.hpp        \\"));
      file.write(QString("    items/foreground.hpp  \\"));
      file.write(QString("    items/signs.hpp       \\"));
      for (int i = 0; i < list.size(); ++i)
      {
        world_item_ptr item = list.at(i);
        if (item->is_level())
          if (level_ptr l = item->level())
            file.write(QString("    stage/level%1.hpp      \\").arg(l->id()));
        if (item->is_boss())
          if (boss_ptr b = item->boss())
            file.write(QString("    stage/boss%1.hpp      \\").arg(b->id()));
        if (item->is_pnj())
          if (pnj_ptr p = item->pnj())
            file.write(QString("    stage/pnj%1.hpp      \\").arg(p->id()));
      }
      file.write(QString("    world%1.hpp            \\").arg(id_));
      file.write(QString(""));
      file.write(QString("SOURCES         =         \\"));
      file.write(QString("    items/background.cpp  \\"));
      file.write(QString("    items/baseground.cpp  \\"));
      file.write(QString("    items/decor.cpp       \\"));
      file.write(QString("    items/death_items.cpp \\"));
      file.write(QString("    items/door.cpp        \\"));
      file.write(QString("    items/foreground.cpp  \\"));
      file.write(QString("    items/signs.cpp       \\"));
      for (int i = 0; i < list.size(); ++i)
      {
        world_item_ptr item = list.at(i);
        if (item->is_level())
          if (level_ptr l = item->level())
            file.write(QString("    stage/level%1.cpp      \\").arg(l->id()));
        if (item->is_boss())
          if (boss_ptr b = item->boss())
            file.write(QString("    stage/boss%1.cpp      \\").arg(b->id()));
        if (item->is_pnj())
          if (pnj_ptr p = item->pnj())
            file.write(QString("    stage/pnj%1.cpp      \\").arg(p->id()));
      }
      file.write(QString("    world%1.cpp            \\").arg(id_));
      file.write(QString(""));
      file.write(QString("RESOURCES       =         \\"));
      file.write(QString("    img/world%1.qrc        \\").arg(id_));

      file.close();
    }

    void world::generate_world_hpp() const
    {
      create_dir_world();

      data::generate file(QString("%1/world%2.hpp").arg(dir_world()).arg(id_));
      file.open();

      file.write(QString("#ifndef WORLD%1_HPP").arg(id_));
      file.write(QString("# define WORLD%1_HPP").arg(id_));
      file.write(QString(""));
      file.write(QString("# ifdef Q_WS_WIN"));
      file.write(QString("#  define MY_EXPORT __declspec(dllexport)"));
      file.write(QString("# else"));
      file.write(QString("#  define MY_EXPORT"));
      file.write(QString("# endif"));
      file.write(QString(""));
      file.write(QString("# include \"core/world.hpp\""));
      file.write(QString(""));
      file.write(QString("namespace world%1").arg(id_));
      file.write(QString("{"));
      file.write(QString(""));
      file.write(QString("  class world%1 : public core::world").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    public:"));
      file.write(QString("      world%1();").arg(id_));
      file.write(QString(""));
      file.write(QString("      virtual int id() const;"));
      file.write(QString("      virtual const QString name() const;"));
      file.write(QString("      virtual const QPixmap pixmap() const;"));
      file.write(QString("      virtual const QPoint pos() const;"));
      file.write(QString("      virtual const QPoint global_pos() const;"));
      file.write(QString(""));
      file.write(QString("  };"));
      file.write(QString(""));
      file.write(QString("  extern \"C\" MY_EXPORT core::world* load()"));
      file.write(QString("  {"));
      file.write(QString("    return new world%1;").arg(id_));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("} // namespace world%1").arg(id_));
      file.write(QString(""));
      file.write(QString("#endif // WORLD%1_HPP").arg(id_));

      file.close();
    }

    void world::generate_world_cpp() const
    {
      const QList<world_item_ptr>& wis = world_items();

      create_dir_world();

      data::generate file(QString("%1/world%2.cpp").arg(dir_world()).arg(id_));
      file.open();

      for (int i = 0; i < wis.size(); ++i)
      {
        world_item_ptr wi = wis.at(i);
        if (wi->is_level())
          if (level_ptr l = wi->level())
            file.write(QString("#include \"stage/level%1.hpp\"").arg(l->id()));
        if (wi->is_boss())
          if (boss_ptr b = wi->boss())
            file.write(QString("#include \"stage/boss%1.hpp\"").arg(b->id()));
        if (wi->is_pnj())
          if (pnj_ptr p = wi->pnj())
            file.write(QString("#include \"stage/pnj%1.hpp\"").arg(p->id()));
      }
      file.write(QString("#include \"world%1.hpp\"").arg(id_));
      file.write(QString(""));
      file.write(QString("namespace world%1").arg(id_));
      file.write(QString("{"));
      file.write(QString(""));
      file.write(QString("  world%1::world%1()").arg(id_));
      file.write(QString("  {"));
      for (int i = 0; i < wis.size(); ++i)
      {
        world_item_ptr wi = wis.at(i);
        switch (wi->type())
        {
          case core::world_item::NONE:
            file.write(QString("    world_item_ptr wi%1 = world_item_ptr(new core::world_item(QPoint(%2, %3)));")
                       .arg(i).arg(wi->pos().x()).arg(wi->pos().y()));
            break;
          case core::world_item::RETURN:
            file.write(QString("    world_item_ptr wi%1 = world_item_ptr(new core::world_item(QPoint(%2, %3), true));")
                       .arg(i).arg(wi->pos().x()).arg(wi->pos().y()));
            break;
          case core::world_item::LEVEL:
            file.write(QString("    level_ptr l%1 = level_ptr(new ::world%1::level%2);")
                       .arg(id_).arg(wi->stage()->id()));
            file.write(QString("    world_item_ptr wi%1 = world_item_ptr(new core::world_item(QPoint(%2, %3), l%4)));")
                       .arg(i).arg(wi->pos().x()).arg(wi->pos().y()).arg(wi->stage()->id()));
            break;
          case core::world_item::BOSS:
            file.write(QString("    boss_ptr b%1 = boss_ptr(new ::world%1::boss%2);")
                       .arg(id_).arg(wi->stage()->id()));
            file.write(QString("    world_item_ptr wi%1 = world_item_ptr(new core::world_item(QPoint(%2, %3), b%4)));")
                       .arg(i).arg(wi->pos().x()).arg(wi->pos().y()).arg(wi->stage()->id()));
            break;
          case core::world_item::PNJ:
            file.write(QString("    pnj_ptr p%1 = pnj_ptr(new ::world%1::pnj%2);")
                       .arg(id_).arg(wi->stage()->id()));
            file.write(QString("    world_item_ptr wi%1 = world_item_ptr(new core::world_item(QPoint(%2, %3), p%4));")
                       .arg(i).arg(wi->pos().x()).arg(wi->pos().y()).arg(wi->stage()->id()));
            break;
        }
        file.write(QString("    add_world_item(wi%1);").arg(i));
      }
      QList<world_item_ptr> already_knows;
      for (int wid1 = 0; wid1 < wis.size(); ++wid1)
      {
        world_item_ptr w1 = wis.at(wid1);
        QMapIterator<world_item_ptr, int> j(w1->connexions());
        while (j.hasNext())
        {
          j.next();
          world_item_ptr w2 = j.key();
          if (not already_knows.contains(w2))
          {
            int wid2 = wis.indexOf(w2);
            int id_door = j.value();
            file.write(QString("    core::world_item::add_connexion(wi%1, wi%2, %3);")
                       .arg(wid1).arg(wid2).arg(id_door));
          }
        }
        already_knows.append(w1);
      }
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString(""));
      file.write(QString("  int world%1::id() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    return %1;").arg(id_));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QString world%1::name() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    return \"%1\";").arg(name_));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QPixmap world%1::pixmap() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    return QPixmap(\":/world%1/world.png\");").arg(id_));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QPoint world%1::pos() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    return QPoint(%1, %2);").arg(pos_.x()).arg(pos_.y()));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QPoint world%1::global_pos() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    return QPoint(%1, %2);").arg(global_pos_.x()).arg(global_pos_.y()));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("} // namespace world%1").arg(id_));

      file.close();
    }

  } // namespace data

} // namespace editor
