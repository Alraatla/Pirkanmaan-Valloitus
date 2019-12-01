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
    int size_;
    std::map<std::string, QColor> tileColors_ = {{"Grassland", QColor(20, 210, 80, 255)},
                                                {"Forest", QColor(120, 150, 90, 255)},
                                                {"Mountain", QColor(180, 180, 180, 255)},
                                                 {"Farm", QColor(52,229,235,255)},
                                                 {"Mine", QColor(235,61,52,255)},
                                                 {"Outpost", QColor(245,133,22,255)},
                                                 {"Water", QColor{0, 119, 190,255}}};
};

} // namespace Team

#endif // MAPITEM_H
