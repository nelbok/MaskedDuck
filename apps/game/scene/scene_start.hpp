#ifndef GAME_SCENE_SCENE_START_HPP
# define GAME_SCENE_SCENE_START_HPP

# include <QGraphicsScene>

namespace game
{

  namespace scene
  {

    /*!
     *  Start's graphics scene.\n
     *  Display the start view.
     */

    class scene_start : public QGraphicsScene
    {
      Q_OBJECT

      public:
        scene_start();

      protected:
        virtual void keyPressEvent(QKeyEvent*);

      private:
        void load();

      signals:
        void sig_return_pushed();
        void sig_escape_pushed();
    };

  } // namespace scene

} // namespace game

#endif // GAME_SCENE_SCENE_START_HPP
