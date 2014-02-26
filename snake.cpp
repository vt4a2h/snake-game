#include "snake.h"

namespace snake {

    Snake::Snake(QObject *parrent)
        : QObject(parrent)
    {
    }

    void Snake::addPart(snake::SnakePart *p)
    {
        if (p->isFree()) {
            snake::SnakePart::Direction d = m_SnakeParts.last()->direction();
            m_SnakeParts.append(p);
            p->setDirection(d);
            p->setFreeStatus(false);
        }
    }

    void Snake::setHead(snake::SnakePart *head)
    {
        if (!m_SnakeParts.isEmpty()) m_SnakeParts.clear();
        m_SnakeParts.append(head);
    }

    snake::SnakePart *Snake::head()
    {
        return m_SnakeParts.isEmpty() ? nullptr : m_SnakeParts.last();
    }

    void Snake::moveDirection()
    {
        m_SnakeParts.last()->moveDirection();

        auto it = m_SnakeParts.end();
        it -= 2;
        for(; it >= m_SnakeParts.begin(); --it) {
            (*it)->setLastPos((*it)->pos());
            (*it)->setPos((*(it + 1))->lastPos());
        }
    }

    void Snake::setDirection(snake::SnakePart::Direction direction)
    {
        m_SnakeParts.last()->setDirection(direction);
    }

    snake::SnakePart::Direction Snake::direction() const
    {
        return m_SnakeParts.last()->direction();
    }

    int Snake::snakeLong() const
    {
        return m_SnakeParts.count();
    }

    SnakeParts Snake::parts() const
    {
        return m_SnakeParts;
    }

} // namespace snake
