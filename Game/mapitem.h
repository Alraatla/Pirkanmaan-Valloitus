#ifndef MAPITEM_H
#define MAPITEM_H

#include "graphics/simplemapitem.h"
#include "core/gameobject.h"
#include <QGraphicsItem>
#include <QPainter>
#include <memory>
#include <map>



namespace Team {


class MapItem : public QGraphicsItem
{
public:
    MapItem(const std::shared_ptr<Course::GameObject> &obj, int size);
    QRectF boundingRect() const final;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    std::shared_ptr<Course::GameObject> getBoundObject();


    void updateLoc();


//    bool isSameObj(std::shared_ptr<Course::GameObject> obj);


//    int getSize() const;

//    void setSize(int size);



private:

    const std::shared_ptr<Course::GameObject> gameObject_;
    QPoint scenelocation_ = QPoint(0,0);
    int size_ = 0;
    std::map<std::string, QColor> tileColors_ = {{"Grassland", QColor(20, 210, 80, 255)},
                                                {"Forest", QColor(120, 150, 90, 255)},
                                                {"Mountain", QColor(180, 180, 180, 255)}};
};

} // namespace Team

#endif // MAPITEM_H
