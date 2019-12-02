#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <memory>
#include <map>

#include "graphics/simplemapitem.h"
#include "core/gameobject.h"



namespace Team {


class MapItem : public Course::SimpleMapItem
{
public:
    MapItem(const std::shared_ptr<Course::GameObject> &obj, int size);
    QRectF boundingRect() const final;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    std::shared_ptr<Course::GameObject> getBoundObject();

private:

    const std::shared_ptr<Course::GameObject> gameObject_;
    QPoint scenelocation_ = QPoint(0,0);
    int size_;
};

} // namespace Team

#endif // MAPITEM_H
