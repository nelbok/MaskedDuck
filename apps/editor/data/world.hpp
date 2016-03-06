#ifndef EDITOR_DATA_WORLD_HPP
# define EDITOR_DATA_WORLD_HPP

# include <QObject>

# include "core/world.hpp"
# include "editor/data/stage/level.hpp"
# include "editor/data/resource.hpp"

class QFile;

namespace editor
{

  namespace data
  {

    /*!
     *  World class.\n
     *  Methods for stages, world item, connexions and management of the saving.
     */

    class world : public QObject, public core::world
    {
      Q_OBJECT

      public:
        world();
        virtual ~world();

        void id(int);
        void name(const QString&);
        void pos(const QPoint&);
        void global_pos(const QPoint&);

        int id() const;
        const QString name() const;
        const QPixmap pixmap() const;
        const QPoint pos() const;
        const QPoint global_pos() const;
        editor_resource_ptr resource() const;

        // Manage stages
        //FIXME: Missing pnj/boss
        editor_level_ptr get_level(world_item_ptr) const;

        // Manage world_item
        //FIXME: Missing pnj/boss
        void add_world_item(const QPoint& pos);
        void add_world_item(const QPoint& pos, editor_level_ptr);
        void modify_world_item(world_item_ptr, const QPoint& new_pos);
        void modify_world_item(world_item_ptr, int id, const QString& name);
        void remove_world_item(world_item_ptr);

        // Manage world_item connexions
        void add_world_item_connexion(world_item_ptr w1, world_item_ptr w2, int id_door = 0);
        void modify_world_item_connexion(world_item_ptr w1, world_item_ptr w2, int id_door = 0);
        void remove_world_item_connexion(world_item_ptr w1, world_item_ptr w2);

        // Management of the saving.
        void load();
        void save() const;
        void generate() const;

        void create_dir_world() const;
        QString dir_world() const;

      private:
        int id_;
        QString name_;
        QPoint pos_;
        QPoint global_pos_;
        editor_resource_ptr resource_;

        QMap<world_item_ptr, editor_level_ptr> levels_;

        QPoint clean_position(const QPoint&) const;

        QString filename_world() const;

        void generate_world_pro() const;
        void generate_world_hpp() const;
        void generate_world_cpp() const;

      signals:
        /*! Signal emitted when the world is updated. */
        void sig_world_updated();

    };

  } // namespace data

} // namespace editor

typedef QSharedPointer<editor::data::world> editor_world_ptr;

#endif // EDITOR_DATA_WORLD_HPP
