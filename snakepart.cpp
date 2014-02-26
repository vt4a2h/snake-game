#include "snakepart.h"

namespace snake {

    SnakePart::SnakePart(QSizeF size, QGraphicsItem *parent)
        : QGraphicsObject(parent)
        , m_Free(true)
        , m_Direction(Right)
        , m_Size(size)
        , m_c(Qt::darkGreen)
    {
    }

    bool SnakePart::isFree() const
    {
        return m_Free;
    }

    void SnakePart::setFreeStatus(bool status)
    {
        m_Free = status;
    }

    void SnakePart::setLastPos(QPointF p)
    {
        m_PreviosState = p;
    }

    QPointF SnakePart::lastPos() const
    {
        return m_PreviosState;
    }

    void SnakePart::moveDirection()
    {
        m_PreviosState = pos();
        switch (m_Direction) {
        case Left:
            moveLeft();
            break;
        case Right:
            moveRight();
            break;
        case Up:
            moveUp();
            break;
        case Down:
            moveDown();
            break;
        }
    }

    SnakePart::Direction SnakePart::direction() const
    {
        return m_Direction;
    }

    void SnakePart::setDirection(Direction direction)
    {
        m_Direction = direction;
    }

    QRectF SnakePart::boundingRect() const
    {
        QPointF leftTop(-m_Size.width() / 2 - MARGIN, -m_Size.height() / 2 - MARGIN);
        QSizeF size(m_Size.width() + MARGIN, m_Size.height() + MARGIN);

        return QRectF(leftTop, size);
    }

    void SnakePart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option)
        Q_UNUSED(widget)

        painter->setBrush(m_c);
        int w = static_cast<int>(m_Size.width() / 2);
        int h = static_cast<int>(m_Size.height() / 2);
        painter->drawEllipse(QPoint(0, 0), w, h);
    }

    void SnakePart::moveLeft()
    {
        moveBy(-m_Size.width(), 0);
    }

    void SnakePart::moveRight()
    {
        moveBy(m_Size.width(), 0);
    }

    void SnakePart::moveUp()
    {
        moveBy(0, -m_Size.height());
    }

    void SnakePart::moveDown()
    {
        moveBy(0, m_Size.height());
    }


    float SnakePart::height() const
    {
        return m_Size.height();
    }

    float SnakePart::width() const
    {
        return m_Size.width();
    }

    void SnakePart::setColor(QColor c)
    {
        prepareGeometryChange();
        m_c = c;
    }

} // namespace graphics_item
