#ifndef GAME_DATA_LEVEL_HPP
# define GAME_DATA_LEVEL_HPP

# include "core/stage/level.hpp"

class QSettings;

namespace game
{

  namespace data
  {

    /*!
     *  Level class.\n
     *  Methods for eggs, lifes, doors and management of the saving.
     */

    class level : public core::no_copy
    {
      public:
        level(level_ptr l);
        virtual ~level();

        /*! To know if a door is opened.
         * \param id_door Identifying of the door.
         * \return true if the door is opened.
         */
        bool open_door(int id_door) const;
        /*! To open a door or not.
         * \param id_door Identifying of the door.
         * \param open true if the door is opened.
         */
        void open_door(int id_door, bool open);

        // Methods for the eggs.
        const QList<bool>& acquired_eggs() const;
        void acquired_egg(int id_egg);
        int nb_acquired_eggs() const;
        int max_eggs() const;

        // Methods for the lifes.
        const QList<bool>& acquired_lifes() const;
        void acquired_life(int id_life);
        int nb_acquired_lifes() const;
        int max_lifes() const;

        // Management of the saving.
        void save(QSettings& s);
        void reset(QSettings& s);
        void load(QSettings& s);

      private:
        QList<bool> open_doors_;
        QList<bool> acquired_eggs_;
        QList<bool> acquired_lifes_;
    };

  } // namespace data

} // namespace game

typedef QSharedPointer<game::data::level> game_level_ptr;

#endif // GAME_DATA_LEVEL_HPP
