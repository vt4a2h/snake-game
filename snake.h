#pragma once

#include <QObject>
#include <QList>

#include <algorithm>

#include "snakepart.h"

namespace snake {

    using SnakeParts = QList<snake::SnakePart*>;

    /*!
     * \brief Класс реализует змейку.
     */
    class Snake : public QObject
    {
        Q_OBJECT
    public:
        explicit Snake(QObject *parrent = nullptr);

        void addPart(snake::SnakePart* p);

        void setHead(snake::SnakePart *head);
        snake::SnakePart *head();

        void moveDirection();

        void setDirection(snake::SnakePart::Direction direction);
        snake::SnakePart::Direction direction() const;

        int snakeLong() const;
        SnakeParts parts() const;

    private:
        SnakeParts m_SnakeParts;
    };

} // namespace snake
