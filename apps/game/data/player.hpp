#ifndef GAME_DATA_PLAYER_HPP
# define GAME_DATA_PLAYER_HPP

# include "core/map.hpp"
# include "game/data/world.hpp"

namespace game
{

  namespace data
  {

    /*!
     *  Player class.\n
     *  Methods for eggs, lifes, doors and management of the saving.
     */

    class player : public core::no_copy
    {
      public:
        player(int id);
        virtual ~player();

        map_ptr map() const;
        world_ptr current_world() const;
        world_item_ptr current_world_item() const;

        void current_world(world_ptr);
        void current_world_item(world_item_ptr);

        int id() const;

        void add_life();
        void remove_life();
        int lifes() const;

        /*! To know if a door is opened.
         * \param l Instance of the level.
         * \param id_door Identifying of the door.
         * \return true if the door is opened.
         */
        bool open_door(level_ptr l, int id_door) const;
        /*! To open a door or not.
         * \param l Instance of the level.
         * \param id_door Identifying of the door.
         * \param open true if the door is opened.
         */
        void open_door(level_ptr l, int id_door, bool open);

        // Methods for the eggs.
        const QList<bool>& acquired_eggs() const;
        void acquired_egg(int id_egg);
        int nb_acquired_eggs(int id_world) const;
        int nb_acquired_eggs() const;
        int max_eggs(int id_world) const;
        int max_eggs() const;

        // Methods for the lifes.
        const QList<bool>& acquired_lifes() const;
        void acquired_life(int id_life);
        int nb_acquired_lifes(int id_world) const;
        int max_lifes(int id_world) const;

        // Management of the saving.
        static QString save_dir();
        void save();
        void reset();
        void load();
        bool new_game() const;

      private:
        map_ptr map_;
        world_ptr current_world_;
        world_item_ptr current_world_item_;
        int id_;
        int lifes_;
        bool new_game_;

        QMap<int, game_world_ptr> worlds_;
    };

  } // namespace data

} // namespace game

typedef QSharedPointer<game::data::player> game_player_ptr;

#endif // GAME_DATA_PLAYER_HPP
