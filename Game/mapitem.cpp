#include "mapitem.h"
#include <QDebug>
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
        addToPoint = QPoint(0, 0);
    }
    else if (gameObject_->getType() == "BasicWorker" ||
             gameObject_->getType() == "Farmer" ||
             gameObject_->getType() == "Miner")
    {
        addToPoint = QPoint(5, 5);
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

    if (    gameObject_->getType() == "BasicWorker")
    {

        painter->drawImage(boundingRect(), QImage(":/worker.png"));
    }
    else if (gameObject_->getType() == "Tyokkari")
    {

        painter->drawImage(boundingRect(),  QImage(":/tyokkari.png"));
    }
    else if (gameObject_->getType() == "Farm")
    {

        painter->drawImage(boundingRect(),  QImage(":/farm.png"));
    }
    else if (gameObject_->getType() == "Mine")
    {

        painter->drawImage(boundingRect(),  QImage(":/mine.png"));
    }
    else if (gameObject_->getType() == "Farmer")
    {

        painter->drawImage(boundingRect(),  QImage(":/farmer.png"));
    }
    else if (gameObject_->getType() == "Miner")
    {

        painter->drawImage(boundingRect(),  QImage(":/miner.png"));
    }
    else if (gameObject_->getType() == "HeadQuarters")
    {

        painter->drawImage(boundingRect(),  QImage(":/headquarters.png"));
    }
    else if (gameObject_->getType() == "Outpost")
    {

        painter->drawImage(boundingRect(),  QImage(":/outpost.png"));
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
