#ifndef GAME_SCENE_GAME_OVER_HPP
# define GAME_SCENE_GAME_OVER_HPP

# include <QGraphicsScene>

namespace game
{

  namespace scene
  {

    /*!
     *  Game Over's graphics scene
     */

    class game_over : public QGraphicsScene
    {
      Q_OBJECT

      public:
        game_over();

      protected:
        virtual void keyPressEvent(QKeyEvent*);

      private:
        void load();

      signals:
        void sig_restart_game();
    };

  } // namespace scene

} // namespace game

#endif // GAME_SCENE_GAME_OVER_HPP
