#ifndef GRAPHICS_ITEM_SNAKEPART_H
#define GRAPHICS_ITEM_SNAKEPART_H

#include <QGraphicsObject>
#include <QPainter>

/*! \brief Составляющие змейки. */
namespace snake {

    /*!
     * \brief Класс реализует одну часть змейки.
     */
    class SnakePart : public QGraphicsObject
    {
        Q_OBJECT
    public:
        enum Direction{Left, Right, Up, Down};

        SnakePart(QSizeF size, QGraphicsItem *parent = 0);

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        Direction direction() const;
        void setDirection(Direction direction);

        bool isFree() const;
        void setFreeStatus(bool status);

        void setLastPos(QPointF p);
        QPointF lastPos() const;

        void moveDirection();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

        float height() const;
        float width() const;

        void setColor(QColor c);

    private:
        static constexpr float MARGIN = 2;

        bool m_Free;
        QPointF m_PreviosState;
        Direction m_Direction;

        QSizeF m_Size;
        QColor m_c;
    };

} // namespace graphics_item

#endif // GRAPHICS_ITEM_SNAKEPART_H
