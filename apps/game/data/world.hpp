#ifndef GAME_DATA_WORLD_HPP
# define GAME_DATA_WORLD_HPP

# include <QMap>

# include "core/world.hpp"
# include "game/data/level.hpp"

class QSettings;

namespace game
{

  namespace data
  {

    /*!
     *  World class.\n
     *  Methods for eggs, lifes, doors and management of the saving.
     */

    class world : public core::no_copy
    {
      public:
        world(world_ptr w);
        virtual ~world();

        /*! To know if a door is opened.
         * \param id_level Identifying of the level.
         * \param id_door Identifying of the door.
         * \return true if the door is opened.
         */
        bool open_door(int id_level, int id_door) const;
        /*! To open a door or not.
         * \param id_level Identifying of the level.
         * \param id_door Identifying of the door.
         * \param open true if the door is opened.
         */
        void open_door(int id_level, int id_door, bool open);

        // Methods for the eggs.
        const QList<bool>& acquired_eggs(int id_level) const;
        void acquired_egg(int id_level, int id_egg);
        int nb_acquired_eggs() const;
        int max_eggs() const;

        // Methods for the lifes.
        const QList<bool>& acquired_lifes(int id_level) const;
        void acquired_life(int id_level, int id_life);
        int nb_acquired_lifes() const;
        int max_lifes() const;

        // Management of the saving.
        void save(QSettings& s);
        void reset(QSettings& s);
        void load(QSettings& s);

      private:
        QMap<int, game_level_ptr> levels_;
    };

  } // namespace data

} // namespace game

typedef QSharedPointer<game::data::world> game_world_ptr;

#endif // GAME_DATA_WORLD_HPP
