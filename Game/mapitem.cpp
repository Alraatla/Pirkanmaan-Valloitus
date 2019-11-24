#include "mapitem.h"
#include <QPixmap>

namespace Team {


MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj,
                 int size):
    gameObject_(obj),
    size_(size),
    scenelocation_(obj->getCoordinatePtr()->asQpoint())
{

}

QRectF MapItem::boundingRect() const
{
    QPoint addToPoint = QPoint(0, 0);

    if(gameObject_->getType() == "Tyokkari" ||
            gameObject_->getType() == "HeadQuarters" ||
            gameObject_->getType() == "Mine" ||
            gameObject_->getType() == "Outpost" ||
            gameObject_->getType() == "Farm")
    {
        addToPoint = QPoint(7, 8);
    }

    return QRectF(scenelocation_ * 50 + addToPoint, scenelocation_ * 50 + QPoint(size_, size_) + addToPoint);
}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );
    QBrush brush = QBrush(QColor(0,0,0,255));
    if(tileColors_.find(gameObject_->getType()) != tileColors_.end()) {
        brush = tileColors_[gameObject_->getType()];
    }
    painter->setBrush(QBrush(brush));

    if (gameObject_->getType() == "Tyokkari")
    {

        painter->drawImage(boundingRect(), QImage("/home/raatala/Documents/OTEK/SOetAR/Game/Images/worker.png"));
    }
    else if (gameObject_->getType() == "HeadQuarters")
    {
        painter->drawImage(boundingRect(), QImage("/home/raatala/Documents/OTEK/SOetAR/Game/Images/headquarters.png"));
    }
    else
    {
        painter->drawRect(boundingRect());
    }



}

std::shared_ptr<Course::GameObject> MapItem::getBoundObject()
{
    return gameObject_;
}


}
