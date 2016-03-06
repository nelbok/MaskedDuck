#ifndef GRAPHICS_ENGINE_SCENE_SCENE_LEVEL_HPP
# define GRAPHICS_ENGINE_SCENE_SCENE_LEVEL_HPP

# include <QGraphicsScene>

# include "core/stage/level.hpp"

namespace graphics_engine
{
  
  class scene_level : public QGraphicsScene
  {
    Q_OBJECT

    public:
      scene_level(QObject* parent = 0);

      void reload(level_ptr l, const QList<bool>& acquired_eggs, const QList<bool>& acquired_lifes);
      void move_background(int dx, int dy);
      void move_background(const QPointF& pos);

    protected:
      // Layers of the view
      QGraphicsItemGroup* backitem_;
      QGraphicsItemGroup* decoitem_;
      QGraphicsItemGroup* signitem_;
      QGraphicsItemGroup* dooritem_;
      QGraphicsItemGroup* lifeitem_;
      QGraphicsItemGroup* eggsitem_;
      QGraphicsItemGroup* baseitem_;
      QGraphicsItemGroup* foreitem_;
      QGraphicsItemGroup* deaditem_;

    private:
      QGraphicsItemGroup* draw_items(const QList<core::block*>&, int depth);

  };
  
} // namespace graphics_engine

#endif // GRAPHICS_ENGINE_SCENE_SCENE_LEVEL_HPP
