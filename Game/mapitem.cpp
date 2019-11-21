#include "mapitem.h"

namespace Team {


MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj,
                 int size):
    size_(size),
    scenelocation_(obj->getCoordinatePtr()->asQpoint()),
    Course::SimpleMapItem(obj, size)
{

}

QRectF MapItem::boundingRect() const
{
    QPoint addToPoint = QPoint(0, 0);
    // Yritin saada että työkkäri ois neliössä alempana kuin HQ
//    if(gameobject_->getType() == "Tyokkari")
//    {
//        addToPoint = QPoint(25, 25);
//    }
    return QRectF(scenelocation_ * 50 + addToPoint, scenelocation_ * 50 + QPoint(size_, size_));
}



}
