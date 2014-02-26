#ifndef GRAPHICS_ITEM_GRID_H
#define GRAPHICS_ITEM_GRID_H

#include <QGraphicsObject>
#include <QPainter>
#include <QLineF>

namespace graphics_item {

    class Grid : public QGraphicsObject
    {
        Q_OBJECT

    public:
        Grid(size_t hCellCount, size_t vCellCount, QSizeF cellSize, QGraphicsItem *parent = 0);

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        float height() const;
        float width() const;
        float margin() const;

    private:
        void drawBorder(QPainter *p);

        static constexpr float MARGIN = 2;

        size_t m_HCellCount;
        size_t m_VCellCount;
        QSizeF m_CellSize;

        float m_Height;
        float m_Width;
    };

} // namespace graphics_item

#endif // GRAPHICS_ITEM_GRID_H
