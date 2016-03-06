#include <QSettings>
#include <QDir>

#include "editor/data/generate.hpp"
#include "editor/data/resource.hpp"
#include "editor/data/world.hpp"

namespace editor
{

  namespace data
  {

    resource::resource(const data::world& w)
      : world_(w)
      , max_id_(-1)
    {
      add_item(QString("block/background.png"),    data::BACKGROUND);
      add_item(QString("block/decor_earth.png"),   data::DECOR);
      add_item(QString("block/decor_ground.png"),  data::DECOR);
      add_item(QString("block/base_earth.png"),    data::BASEGROUND);
      add_item(QString("block/base_ground.png"),   data::BASEGROUND);
      add_item(QString("block/fore_earth.png"),    data::FOREGROUND);
      add_item(QString("block/fore_ground.png"),   data::FOREGROUND);
    }

    resource::~resource()
    {
    }


    void resource::add_item(const QString& filename, data::type_item type)
    {
      ++max_id_;
      data::item i;
      i.id_ = max_id_;
      i.filename_ = filename;
      i.type_ = type;
      items_.append(i);

      emit sig_resource_updated();
    }

    void resource::remove_item(int index)
    {
      Q_ASSERT(0 <= index and index < items_.size());
      items_.removeAt(index);
      emit sig_resource_updated();
    }

    void resource::replace_item(int index, data::item i)
    {
      Q_ASSERT(0 <= index and index < items_.size());
      items_.replace(index, i);
      emit sig_resource_updated();
    }

    const data::item& resource::item(int index) const
    {
      Q_ASSERT(items_.size() > index);
      return items_.at(index);
    }

    const QList<data::item>& resource::items() const
    {
      return items_;
    }


    QString resource::str_type_item(data::type_item type) const
    {
      switch (type)
      {
        case BACKGROUND:  return QString("Background");
        case DECOR:       return QString("Decor");
        case SIGN:        return QString("Sign");
        case DOOR:        return QString("Door");
        case BASEGROUND:  return QString("Baseground");
        case FOREGROUND:  return QString("Foreground");
        case DEATH_ITEM:  return QString("Death item");

        case EGG:
        case LIFE:
        case SIZE:        break;
      }

      return QString("Error");
    }

    QString resource::img_filename(const data::item& res) const
    {
      return QString("%1/img/%2").arg(world_.dir_world()).arg(res.filename_);
    }


    void resource::load(QSettings& s)
    {
      items_.clear();

      s.beginGroup("resource");
      max_id_ = s.value("max_id").toInt();

      int size = s.beginReadArray("items");
      for (int i = 0; i < size; ++i)
      {
        data::item res;

        s.setArrayIndex(i);
        res.id_ = s.value("id").toInt();
        res.filename_ = s.value("filename").toString();
        res.type_ = data::type_item(s.value("type").toInt());

        items_.append(res);
      }
      s.endArray();

      emit sig_resource_updated();
    }

    void resource::save(QSettings& s) const
    {
      s.beginGroup("resource");
      s.setValue("max_id", QVariant(max_id_));

      s.beginWriteArray("items");
      for (int i = 0; i < items_.size(); ++i)
      {
        data::item res = items_.at(i);

        s.setArrayIndex(i);
        s.setValue("id", QVariant(res.id_));
        s.setValue("filename", QVariant(res.filename_));
        s.setValue("type", QVariant(res.type_));
      }
      s.endArray();
    }

    void resource::generate() const
    {
      generate_img_world_qrc();
      generate_items_all_hpp();

      QStringList backgrounds_;
      QStringList decors_;
      QStringList signs_;
      QStringList doors_;
      QStringList basegrounds_;
      QStringList foregrounds_;
      QStringList death_items_;

      backgrounds_.append("block/background.png");

      for (int i = 0; i < items_.size(); ++i)
      {
        data::item res = items_.at(i);
        switch (res.type_)
        {
          case data::BACKGROUND:  backgrounds_.append(res.filename_); break;
          case data::DECOR:       decors_.append(res.filename_); break;
          case data::SIGN:        signs_.append(res.filename_); break;
          case data::DOOR:        doors_.append(res.filename_); break;
          case data::BASEGROUND:  basegrounds_.append(res.filename_); break;
          case data::FOREGROUND:  foregrounds_.append(res.filename_); break;
          case data::DEATH_ITEM:  death_items_.append(res.filename_); break;

          case data::EGG:
          case data::LIFE:
          case data::SIZE:        break;
        }
      }

      generate_items_template_hpp(backgrounds_, QString("BACKGROUND"),  QString("background"));
      generate_items_template_hpp(decors_,      QString("DECOR"),       QString("decor"));
      generate_items_template_hpp(signs_,       QString("SIGNS"),       QString("signs"));
      generate_items_template_hpp(doors_,       QString("DOOR"),        QString("door"));
      generate_items_template_hpp(basegrounds_, QString("BASEGROUND"),  QString("baseground"));
      generate_items_template_hpp(foregrounds_, QString("FOREGROUND"),  QString("foreground"));
      generate_items_template_hpp(death_items_, QString("DEATH_ITEMS"), QString("death_items"));

      generate_items_template_cpp(backgrounds_, QString("background"));
      generate_items_template_cpp(decors_,      QString("decor"));
      generate_items_template_cpp(signs_,       QString("signs"));
      generate_items_template_cpp(doors_,       QString("door"));
      generate_items_template_cpp(basegrounds_, QString("baseground"));
      generate_items_template_cpp(foregrounds_, QString("foreground"));
      generate_items_template_cpp(death_items_, QString("death_items"));
    }


    void resource::generate_img_world_qrc() const
    {
      world_.create_dir_world();
      QString path = world_.dir_world();

      QDir d(path);
      d.mkdir(QString("img/"));

      data::generate file(QString("%1/img/world%2.qrc").arg(path).arg(world_.id()));
      file.open(data::generate::RCC_FILE);

      file.write(QString("<!DOCTYPE RCC><RCC version=\"1.0\">"));
      file.write(QString("<qresource prefix=\"/world%1\">").arg(world_.id()));
      file.write(QString("    <file>world.png</file>"));
      file.write(QString("    <file>block/background.png</file>"));
      for (int i = 0; i < items_.size(); ++i)
      {
        file.write(QString("    <file>%1</file>").arg(items_.at(i).filename_));
      }
      file.write(QString("</qresource>"));
      file.write(QString("</RCC>"));

      file.close();
    }

    void resource::generate_items_all_hpp() const
    {
      world_.create_dir_world();
      int id = world_.id();
      QString path = world_.dir_world();

      QDir d(path);
      d.mkdir(QString("items/"));

      data::generate file(QString("%1/items/all.hpp").arg(path));
      file.open();

      file.write(QString("#ifndef WORLD%1_ALL_ITEMS_HPP").arg(id));
      file.write(QString("# define WORLD%1_ALL_ITEMS_HPP").arg(id));
      file.write(QString(""));
      file.write(QString("# include \"background.hpp\""));
      file.write(QString("# include \"baseground.hpp\""));
      file.write(QString("# include \"decor.hpp\""));
      file.write(QString("# include \"death_items.hpp\""));
      file.write(QString("# include \"door.hpp\""));
      file.write(QString("# include \"foreground.hpp\""));
      file.write(QString("# include \"signs.hpp\""));
      file.write(QString(""));
      file.write(QString("#endif // WORLD%1_ALL_ITEMS_HPP").arg(id));

      file.close();
    }

    void resource::generate_items_template_hpp(const QStringList& list, const QString& def, const QString& basename) const
    {
      world_.create_dir_world();
      int id = world_.id();
      QString path = world_.dir_world();

      QDir d(path);
      d.mkdir(QString("items/"));

      data::generate file(QString("%1/items/%2.hpp").arg(path).arg(basename));
      file.open();

      file.write(QString("#ifndef WORLD%1_ITEMS_%2_HPP").arg(id).arg(def));
      file.write(QString("# define WORLD%1_ITEMS_%2_HPP").arg(id).arg(def));
      file.write(QString(""));
      file.write(QString("# include \"core/items/block.hpp\""));
      file.write(QString(""));
      file.write(QString("namespace world%1").arg(id));
      file.write(QString("{"));
      file.write(QString(""));
      for (int i = 0; i < list.size(); ++i)
      {
        QFileInfo fi (list.at(i));
        const QString& name = fi.baseName();
        file.write(QString("  class %1 : public core::block").arg(name));
        file.write(QString("  {"));
        file.write(QString("    public:"));
        file.write(QString("      %1(const QPoint& pos, int width = 0, int height = 0);").arg(name));
        file.write(QString("  };"));
        file.write(QString(""));
      }
      file.write(QString("} // namespace world%1").arg(id));
      file.write(QString(""));
      file.write(QString("#endif // WORLD%1_ITEMS_%2_HPP").arg(id).arg(def));

      file.close();
    }

    void resource::generate_items_template_cpp(const QStringList& list, const QString& basename) const
    {
      world_.create_dir_world();
      int id = world_.id();
      QString path = world_.dir_world();

      QDir d(path);
      d.mkdir(QString("items/"));

      data::generate file(QString("%1/items/%2.cpp").arg(path).arg(basename));
      file.open();

      file.write(QString("#include \"%1.hpp\"").arg(basename));
      file.write(QString(""));
      file.write(QString("namespace world%1").arg(id));
      file.write(QString("{"));
      file.write(QString(""));
      for (int i = 0; i < list.size(); ++i)
      {
        const QString& filename = list.at(i);
        QFileInfo fi (filename);
        const QString& name = fi.baseName();
        file.write(QString("  %1::%1(const QPoint& pos, int width, int height)").arg(name));
        file.write(QString("    : core::block(\":/world%1/%2\", pos, width, height)").arg(id).arg(filename));
        file.write(QString("  {"));
        file.write(QString("  }"));
        file.write(QString(""));
      }
      file.write(QString("} // namespace world%1").arg(id));

      file.close();
    }

  } // namespace data

} // namespace editor
