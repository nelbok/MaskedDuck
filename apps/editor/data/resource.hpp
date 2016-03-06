#ifndef EDITOR_DATA_RESOURCE_HPP
# define EDITOR_DATA_RESOURCE_HPP

# include <QObject>

# include "core/no_copy.hpp"

class QSettings;

namespace editor
{

  namespace data
  {
    /*!
     *  List of the different type of block.
     */

    enum type_item
    {
      BACKGROUND,
      DECOR,
      SIGN,
      DOOR,
      BASEGROUND,
      FOREGROUND,
      DEATH_ITEM,

      EGG,
      LIFE,

      SIZE
    };

    /*!
     *  Structure of a item.\n
     *  Have a identifying, a type and a file path.
     */

    struct item
    {
      item() : id_(-1), type_(data::SIZE) {}

      int id_;
      QString filename_;
      data::type_item type_;
    };

    class world;

    /*!
     *  Resource class.\n
     *  Methods for stages, world item, connexions and management of the saving.
     */

    class resource : public QObject, public core::no_copy
    {
      Q_OBJECT

      public:
        resource(const data::world& w);
        virtual ~resource();

        // Methods for the items
        void add_item(const QString& filename, data::type_item type);
        void remove_item(int index);
        void replace_item(int index, data::item);
        const data::item& item(int index) const;
        const QList<data::item>& items() const;

        QString str_type_item(data::type_item) const;
        QString img_filename(const data::item&) const;

        // Management of the saving
        void load(QSettings&);
        void save(QSettings&) const;
        void generate() const;

      private:
        const data::world& world_;
        int max_id_;

        QList<data::item> items_;

        void generate_img_world_qrc() const;
        void generate_items_all_hpp() const;
        void generate_items_template_hpp(const QStringList&, const QString& def, const QString& basename) const;
        void generate_items_template_cpp(const QStringList&, const QString& basename) const;

      signals:
        /*! Signal emitted when the resource is updated. */
        void sig_resource_updated();
    };

  } // namespace data

} // namespace editor

typedef QSharedPointer<editor::data::resource> editor_resource_ptr;

#endif // EDITOR_DATA_RESOURCE_HPP
