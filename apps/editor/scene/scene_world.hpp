#ifndef EDITOR_SCENE_SCENE_WORLD_HPP
# define EDITOR_SCENE_SCENE_WORLD_HPP

# include <QGraphicsScene>

# include "editor/data/world.hpp"

namespace editor
{

  namespace scene
  {

    /*!
     *  Graphics scene for the world.\n
     *  Show the world.
     */

    class world : public QGraphicsScene
    {
      Q_OBJECT

      public:
        world(editor_world_ptr w);

      private slots:
        void do_reload();

      private:
        void draw_background(int depth);
        void draw_baseground(int depth);

        void draw_road(QGraphicsItemGroup* group, world_item_ptr w1, world_item_ptr w2, int id_door);
        void draw_world_item(QGraphicsItemGroup* group, world_item_ptr data);

        editor_world_ptr world_;
    };

  } // namespace scene

} // namespace editor

#endif // EDITOR_SCENE_SCENE_WORLD_HPP
