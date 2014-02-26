#include "grid.h"

namespace graphics_item {

    Grid::Grid(size_t hCellCount, size_t vCellCount, QSizeF cellSize, QGraphicsItem *parent)
        : QGraphicsObject(parent)
        , m_HCellCount(hCellCount)
        , m_VCellCount(vCellCount)
        , m_CellSize(cellSize)
        , m_Height(m_VCellCount * m_CellSize.height())
        , m_Width(m_HCellCount * m_CellSize.width())
    {
    }

    QRectF Grid::boundingRect() const
    {
        QPointF leftTop(-m_Width / 2 - MARGIN, -m_Height / 2 - MARGIN);
        QSizeF  size(m_Width + MARGIN, m_Height + MARGIN);
        return QRectF(leftTop, size);
    }

    void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option)
        Q_UNUSED(widget)

        drawBorder(painter);
//        drawLines(painter);
    }

    void Grid::drawBorder(QPainter *p)
    {
        p->save();
        p->setPen(Qt::darkRed);
        p->drawRect(QRectF(-m_Width / 2, -m_Height / 2, m_Width, m_Height));
        p->restore();
    }

    float Grid::width() const
    {
        return m_Width;
    }

    float Grid::margin() const
    {
        return MARGIN;
    }

    float Grid::height() const
    {
        return m_Height;
    }

} // namespace graphics_item
