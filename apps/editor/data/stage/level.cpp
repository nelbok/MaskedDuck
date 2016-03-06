#include <QSettings>
#include <QDir>

#include "core/items/block.hpp"

#include "editor/data/generate.hpp"
#include "editor/data/stage/level.hpp"
#include "editor/data/world.hpp"

namespace editor
{

  namespace data
  {

    level::level(const data::world& w, int id, const QString& name)
      : world_(w)
      , id_(id)
      , name_(name)
    {
      const QList<data::item>& l = w.resource()->items();
      for (int i = 0; i < l.size(); ++i)
      {
        const data::item& res = l.at(i);
        if (res.type_ == editor::data::BACKGROUND)
          add_item_(res, QRect(0, 0, 800, 600));
      }
    }

    level::~level()
    {
    }


    int level::id() const
    {
      return id_;
    }

    const QString level::name() const
    {
      return name_;
    }


    void level::id(int i)
    {
      id_ = i;
      emit sig_level_updated();
    }

    void level::name(const QString& n)
    {
      name_ = n;
      emit sig_level_updated();
    }


    const QPoint level::start_position() const
    {
      return start_position_;
    }

    const QList<core::block*> level::background() const
    {
      return items(data::BACKGROUND);
    }

    const QList<core::block*> level::decor() const
    {
      return items(data::DECOR);
    }

    const QList<core::block*> level::signs() const
    {
      return items(data::SIGN);
    }

    const QList<core::block*> level::doors() const
    {
      return items(data::DOOR);
    }

    const QList<core::block*> level::eggs(const QList<bool>&) const
    {
      return items(data::EGG);
    }

    const QList<core::block*> level::lifes(const QList<bool>&) const
    {
      return items(data::LIFE);
    }

    const QList<core::block*> level::baseground() const
    {
      return items(data::BASEGROUND);
    }

    const QList<core::block*> level::foreground() const
    {
      return items(data::FOREGROUND);
    }

    const QList<core::block*> level::death_items() const
    {
      return items(data::DEATH_ITEM);
    }


    const QList<core::block*> level::items(data::type_item type) const
    {
      QList<core::block*> list;

      const QList<QPair<int, QRect> >& datas = data(type);

      for (int i = 0; i < datas.size(); ++i)
      {
        int id_resource = datas.at(i).first;
        QRect r = datas.at(i).second;

        //Create file path to the image
        editor_resource_ptr res = world_.resource();
        const data::item& one_res = res->item(id_resource);

        core::block* item = new core::block(res->img_filename(one_res), QPoint(r.x(), r.y()), r.width(), r.height());
        item->setData(Qt::UserRole + 1, QVariant(type));
        item->setData(Qt::UserRole + 2, QVariant(i));
        list.append(item);
      }

      return list;
    }

    void level::add_item(const data::item& res, const QRect& rect)
    {
      if (res.type_ == editor::data::BACKGROUND)
        return;

      add_item_(res, rect);

      emit sig_level_updated();
    }

    void level::add_item_(const data::item& res, const QRect& rect)
    {
      QList<QPair<int, QRect> >& datas = data(res.type_);

      for (int i = 0; i < datas.size(); ++i)
        if (rect.intersects(datas.at(i).second))
          return;

      datas.append(QPair<int, QRect>(res.id_, rect));
    }

    void level::remove_item(data::type_item type, const QRect& rect)
    {
      if (type == editor::data::BACKGROUND)
        return;

      if (remove_item_(type, rect))
        emit sig_level_updated();
    }

    bool level::remove_item_(data::type_item type, const QRect& rect)
    {
      QList<QPair<int, QRect> >& datas = data(type);
      QList<QPair<int, QRect> > tmp = datas;

      for (int i = 0; i < tmp.size(); ++i)
        if (rect.intersects(tmp.at(i).second))
        {
          datas.removeAll(tmp.at(i));
          return true;
        }

      return false;
    }


    void level::load(QSettings& s)
    {
      s.beginGroup(QString("level%1").arg(id_));
      name_ = s.value("name").toString();
      start_position_ = s.value("start_position").toPoint();

      load_list("background", background_, s);
      load_list("decor", decor_, s);
      load_list("signs", signs_, s);
      load_list("doors", doors_, s);
      load_list("eggs", eggs_, s);
      load_list("lifes", lifes_, s);
      load_list("baseground", baseground_, s);
      load_list("foreground", foreground_, s);
      load_list("death_items", death_items_, s);

      s.endGroup();

      emit sig_level_updated();
    }

    void level::load_list(const QString& name, QList<QPair<int, QRect> >& list, QSettings& s)
    {
      int size = s.beginReadArray(name);
      for (int i = 0; i < size; ++i)
      {
        s.setArrayIndex(i);

        QPair<int, QRect> item (s.value("id_resource").toInt(),
                                s.value("rect").toRect());

        list.append(item);
      }
      s.endArray();
    }

    void level::save(QSettings& s) const
    {
      s.beginGroup(QString("level%1").arg(id_));
      s.setValue("name", QVariant(name_));
      s.setValue("start_position", QVariant(start_position_));

      save_list("background", background_, s);
      save_list("decor", decor_, s);
      save_list("signs", signs_, s);
      save_list("doors", doors_, s);
      save_list("eggs", eggs_, s);
      save_list("lifes", lifes_, s);
      save_list("baseground", baseground_, s);
      save_list("foreground", foreground_, s);
      save_list("death_items", death_items_, s);

      s.endGroup();
    }

    void level::save_list(const QString& name, const QList<QPair<int, QRect> >& list, QSettings& s) const
    {
      s.beginWriteArray(name);
      for (int i = 0; i < list.size(); ++i)
      {
        const QPair<int, QRect>& item = list.at(i);

        s.setArrayIndex(i);
        s.setValue("id_resource", QVariant(item.first));
        s.setValue("rect", QVariant(item.second));
      }
      s.endArray();
    }

    void level::generate() const
    {
      generate_stage_level_hpp();
      generate_stage_level_cpp();
    }


    QList<QPair<int, QRect> >& level::data(data::type_item type)
    {
      switch(type)
      {
        case data::BACKGROUND:  return background_;
        case data::DECOR:       return decor_;
        case data::SIGN:        return signs_;
        case data::DOOR:        return doors_;
        case data::BASEGROUND:  return baseground_;
        case data::FOREGROUND:  return foreground_;
        case data::DEATH_ITEM:  return death_items_;

        case data::EGG:         return eggs_;
        case data::LIFE:        return lifes_;

        case data::SIZE:        break;
      }

      return background_;
    }

    const QList<QPair<int, QRect> >& level::data(data::type_item type) const
    {
      switch(type)
      {
        case data::BACKGROUND:  return background_;
        case data::DECOR:       return decor_;
        case data::SIGN:        return signs_;
        case data::DOOR:        return doors_;
        case data::BASEGROUND:  return baseground_;
        case data::FOREGROUND:  return foreground_;
        case data::DEATH_ITEM:  return death_items_;

        case data::EGG:         return eggs_;
        case data::LIFE:        return lifes_;

        case data::SIZE:        break;
      }

      return background_;
    }


    void level::generate_stage_level_hpp() const
    {
      world_.create_dir_world();
      int id_world = world_.id();
      QString path = world_.dir_world();

      QDir d(path);
      d.mkdir(QString("stage/"));

      data::generate file(QString("%1/stage/level%2.hpp").arg(path).arg(id_));
      file.open();

      file.write(QString("#ifndef WORLD%1_LEVEL%2_HPP").arg(id_world).arg(id_));
      file.write(QString("# define WORLD%1_LEVEL%2_HPP").arg(id_world).arg(id_));
      file.write(QString(""));
      file.write(QString("# include <QList>"));
      file.write(QString(""));
      file.write(QString("# include \"core/stage/level.hpp\""));
      file.write(QString(""));
      file.write(QString("namespace world%1").arg(id_world));
      file.write(QString("{"));
      file.write(QString(""));
      file.write(QString("  class level%1 : public stage::level").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    public:"));
      file.write(QString("      level%1();").arg(id_));
      file.write(QString(""));
      file.write(QString("      virtual int id() const;"));
      file.write(QString("      virtual const QString name() const;"));
      file.write(QString(""));
      file.write(QString("      virtual const QPoint start_position() const;"));
      file.write(QString("      virtual const QList<core::block*> background() const;"));
      file.write(QString("      virtual const QList<core::block*> decor() const;"));
      file.write(QString("      virtual const QList<core::block*> signs() const;"));
      file.write(QString("      virtual const QList<core::block*> doors() const;"));
      file.write(QString("      virtual const QList<core::block*> eggs(const QList<bool>& already_acquired) const;"));
      file.write(QString("      virtual const QList<core::block*> lifes(const QList<bool>& already_acquired) const;"));
      file.write(QString("      virtual const QList<core::block*> baseground() const;"));
      file.write(QString("      virtual const QList<core::block*> foreground() const;"));
      file.write(QString("      virtual const QList<core::block*> death_items() const;"));
      file.write(QString("  };"));
      file.write(QString(""));
      file.write(QString("} // namespace world%1").arg(id_world));
      file.write(QString(""));
      file.write(QString("#endif // WORLD%1_LEVEL%2_HPP").arg(id_world).arg(id_));

      file.close();
    }

    void level::generate_stage_level_cpp() const
    {
      world_.create_dir_world();
      int id_world = world_.id();
      QString path = world_.dir_world();

      QDir d(path);
      d.mkdir(QString("stage/"));

      data::generate file(QString("%1/stage/level%2.cpp").arg(path).arg(id_));
      file.open();

      file.write(QString("#include \"items/all.hpp\""));
      file.write(QString(""));
      file.write(QString("#include \"level%1.hpp\"").arg(id_));
      file.write(QString(""));
      file.write(QString("namespace world%1").arg(id_world));
      file.write(QString("{"));
      file.write(QString(""));
      file.write(QString("  level%1::level%1()").arg(id_));
      file.write(QString("  {"));
      file.write(QString(""));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString(""));
      file.write(QString("  int level%1::id() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    return %1;").arg(id_));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QString level%1::name() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    return \"%1\";").arg(name_));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString(""));
      file.write(QString("  const QPoint level%1::start_position() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    return QPoint(%1, %2);").arg(start_position_.x()).arg(start_position_.y()));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::background() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::decor() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::signs() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::doors() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::eggs(const QList<bool>& already_acquired) const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    Q_ASSERT(true));"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::lifes(const QList<bool>& already_acquired) const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    Q_ASSERT(true));"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::baseground() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::foreground() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("  const QList<core::block*> level%1::death_items() const").arg(id_));
      file.write(QString("  {"));
      file.write(QString("    QList<core::block*> l;"));
      file.write(QString(""));
      file.write(QString("    return l;"));
      file.write(QString("  }"));
      file.write(QString(""));
      file.write(QString("} // namespace world%1").arg(id_world));

      file.close();
    }

  } // namespace data

} // namespace editor
