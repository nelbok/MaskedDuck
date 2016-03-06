#ifndef CORE_ITEMS_BLOCK_HPP
# define CORE_ITEMS_BLOCK_HPP

# include <QGraphicsItem>

namespace core
{
  
  /*!
   *  Main class of all the blocks being of use to the display.
   */

  class block : public QGraphicsItem
  {
    public:
      /*!
       *  Construct a block.
       * \param img The image used to paint the background of the block.
       * \param pos Position of the block.
       * \param width Width of the block, by default the width of the image.
       * \param height Height of the block, by default the height of the image.
       */
      block(const QString& img, const QPoint& pos, int width = 0, int height = 0);

      QRectF boundingRect() const;
      void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget);
      QPainterPath shape() const;

    private:
      int width_;
      int height_;
      QPixmap img_;
  };

} // namespace core

#endif // CORE_ITEMS_BLOCK_HPP
