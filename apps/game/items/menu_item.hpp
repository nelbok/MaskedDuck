#ifndef GAME_ITEMS_MENU_ITEM_HPP
# define GAME_ITEMS_MENU_ITEM_HPP

# include <QGraphicsItemGroup>

namespace game
{

  namespace items
  {

    /*!
     *  Menu's graphics item.\n
     *  Use in all the scenes.
     */

    class menu_item : public QGraphicsItemGroup
    {
      public:
        /*! Configuration of the menu. */
        enum menu_type
        {
          SCENE_LEVEL,  /*!< For scene level. */
          SCENE_WORLD,  /*!< For scene world. */
          SELECT_WORLD  /*!< For select world. */
        };

        /*! Various choices possible of the menu. */
        enum selection_type
        {
          CONTINUE,     /*!< To continue, default choice. */
          RETURN_MAP,   /*!< To returm on the select world. */
          QUIT_LEVEL,   /*!< Quit a level. */
          QUIT_GAME     /*!< Quit the game. */
        };

        menu_item(menu_item::menu_type type);

        void move_to_up();
        void move_to_down();
        menu_item::selection_type current_selection() const;

      private:
        void init();
        void draw_text(const QString& text, int y_offset);
        void move_duck();

        int nb_choices_;
        int current_choice_;
        QGraphicsItem* duck_;
        menu_item::menu_type type_;

    };

  } // namespace items

} // namespace game

#endif // GAME_ITEMS_MENU_ITEM_HPP
