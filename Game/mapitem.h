#ifndef MAPITEM_H
#define MAPITEM_H

#include "graphics/simplemapitem.h"
#include "core/gameobject.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>


namespace Team {


class MapItem : public Course::SimpleMapItem
{
public:
    MapItem(const std::shared_ptr<Course::GameObject> &obj, int size);
    QRectF boundingRect() const final;

private:
    QPoint scenelocation_ = QPoint(0,0);
    int size_ = 0;
};

}

#endif // MAPITEM_H
