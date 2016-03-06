#ifndef CORE_WORLD_ITEM_HPP
# define CORE_WORLD_ITEM_HPP

# include <QPoint>
# include <QMap>

# include "core/stage/boss.hpp"
# include "core/stage/level.hpp"
# include "core/stage/pnj.hpp"
# include "core/no_copy.hpp"

//FIXME: Make template class

namespace core
{
  class world_item;
}

typedef QSharedPointer<core::world_item> world_item_ptr;

namespace core
{
  /*!
   *  Class abstracted from a world item, can contains a stage. \n
   *  Contains a map of connection to the another world items.
   */

  class world_item : public no_copy
  {
    public:
      /*! Different type of a world item. */
      enum item_type
      {
        NONE,   /*!< Just a point on the map. */
        RETURN, /*!< Allow to go in a another world. */
        LEVEL,  /*!< Level stage. */
        BOSS,   /*!< Boss stage. */
        PNJ     /*!< Pnj stage. */
      };

      world_item(const QPoint& pos, boss_ptr data);
      world_item(const QPoint& pos, level_ptr data);
      world_item(const QPoint& pos, pnj_ptr data);
      world_item(const QPoint& pos, bool return_type = false);
      virtual ~world_item();

      const QPoint& pos() const;
      world_item::item_type type() const;

      void pos(const QPoint&);
      void type(world_item::item_type);

      // Test the type of the world item.
      bool is_stage() const;
      bool is_boss() const;
      bool is_level() const;
      bool is_pnj() const;

      // Return the data pointer of the world item.
      stage_ptr stage() const;
      boss_ptr boss() const;
      level_ptr level() const;
      pnj_ptr pnj() const;

      /*! Methods to manage the connexion between two world items.
       *  Each methods work on the two world items in the same time.
       * \param w1 First world item.
       * \param w2 Second world item.
       * \param id_door If there is a door. (optionnal)
       */
      static void add_connexion(world_item_ptr w1, world_item_ptr w2, int id_door = 0);
      /*! Methods to manage the connexion between two world items.
       *  Each methods work on the two world items in the same time.
       * \param w1 First world item.
       * \param w2 Second world item.
       * \param id_door If there is a door. (optionnal)
       */
      static void modify_connexion(world_item_ptr w1, world_item_ptr w2, int id_door = 0);
      /*! Methods to manage the connexion between two world items.
       *  Each methods work on the two world items in the same time.
       * \param w1 First world item.
       * \param w2 Second world item.
       */
      static void remove_connexion(world_item_ptr w1, world_item_ptr w2);
      /*! Methods to manage the connexion between two world items.
       *  Each methods work on the two world items in the same time.
       * \param w1 World item.
       */
      static void clear_connexions(world_item_ptr w1);
      bool contains_connexion(world_item_ptr item) const;
      const QMap<world_item_ptr, int>& connexions() const;

    private:
      QPoint pos_;
      world_item::item_type type_;
      QMap<world_item_ptr, int> connexions_;
      boss_ptr boss_;
      level_ptr level_;
      pnj_ptr pnj_;
      stage_ptr stage_;
  };
  
} // namespace core

#endif // CORE_WORLD_ITEM_HPP
