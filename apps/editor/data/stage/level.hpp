#ifndef EDITOR_DATA_LEVEL_HPP
# define EDITOR_DATA_LEVEL_HPP

# include <QObject>
# include <QPoint>
# include <QPair>
# include <QRect>

# include "core/stage/level.hpp"

# include "editor/data/resource.hpp"

class QSettings;

namespace editor
{

  namespace data
  {
    class world;

    /*!
     *  Level class.
     */

    class level : public QObject, public core::level
    {
      Q_OBJECT

      public:
        level(const data::world& w, int id, const QString& name = QString(""));
        virtual ~level();

        virtual int id() const;
        virtual const QString name() const;
        void id(int);
        void name(const QString&);

        // Reimplementation of the layers of display.
        virtual const QPoint start_position() const;
        virtual const QList<core::block*> background() const;
        virtual const QList<core::block*> decor() const;
        virtual const QList<core::block*> signs() const;
        virtual const QList<core::block*> doors() const;
        virtual const QList<core::block*> eggs(const QList<bool>& already_acquired) const;
        virtual const QList<core::block*> lifes(const QList<bool>& already_acquired) const;
        virtual const QList<core::block*> baseground() const;
        virtual const QList<core::block*> foreground() const;
        virtual const QList<core::block*> death_items() const;

        // Methods for the items.
        const QList<core::block*> items(data::type_item type) const;
        void add_item(const data::item& res, const QRect& rect);
        void remove_item(data::type_item type, const QRect& rect);

        // Management of the saving.
        void load(QSettings&);
        void load_list(const QString& name, QList<QPair<int, QRect> >& list, QSettings&);
        void save(QSettings&) const;
        void save_list(const QString& name, const QList<QPair<int, QRect> >& list, QSettings&) const;
        void generate() const;

      private:
        const data::world& world_;
        int id_;
        QString name_;

        void add_item_(const data::item& res, const QRect& rect);
        bool remove_item_(data::type_item type, const QRect& rect);

        QPoint start_position_;
        QList<QPair<int, QRect> > background_;
        QList<QPair<int, QRect> > decor_;
        QList<QPair<int, QRect> > signs_;
        QList<QPair<int, QRect> > doors_;
        QList<QPair<int, QRect> > eggs_;
        QList<QPair<int, QRect> > lifes_;
        QList<QPair<int, QRect> > baseground_;
        QList<QPair<int, QRect> > foreground_;
        QList<QPair<int, QRect> > death_items_;

        QList<QPair<int, QRect> >& data(data::type_item type);
        const QList<QPair<int, QRect> >& data(data::type_item type) const;

        void generate_stage_level_hpp() const;
        void generate_stage_level_cpp() const;

      signals:
        void sig_level_updated();
    };

  } // namespace data

} // namespace editor

typedef QSharedPointer<editor::data::level> editor_level_ptr;

#endif // EDITOR_DATA_LEVEL_HPP
