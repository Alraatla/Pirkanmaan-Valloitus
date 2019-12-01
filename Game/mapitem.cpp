#include "mapitem.h"
#include <QDebug>
#include <QPixmap>

namespace Team {


MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj,
                 int size):
    gameObject_(obj),
    scenelocation_(obj->getCoordinatePtr()->asQpoint()),
    size_(size)
{

}

QRectF MapItem::boundingRect() const
{
    QPoint addToPoint = QPoint(0, 0);

    if(gameObject_->getType() == "Tyokkari" ||
            gameObject_->getType() == "HeadQuarters" ||
            gameObject_->getType() == "Mine" ||
            gameObject_->getType() == "Outpost" ||
            gameObject_->getType() == "Farm" ||
            gameObject_->getType() == "Grassland" ||
            gameObject_->getType() == "Forest" ||
            gameObject_->getType() == "Mountain" ||
            gameObject_->getType() == "Water")
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
    painter->setBrush(QBrush(brush));

    if (    gameObject_->getType() == "BasicWorker")
    {

        painter->drawImage(boundingRect(), QImage(":/images/worker.png"));
    }
    else if (gameObject_->getType() == "Tyokkari")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/tyokkari.png"));
    }
    else if (gameObject_->getType() == "Farm")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/farm.png"));
    }
    else if (gameObject_->getType() == "Mine")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/mine.png"));
    }
    else if (gameObject_->getType() == "Farmer")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/farmer.png"));
    }
    else if (gameObject_->getType() == "Miner")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/miner.png"));
    }
    else if (gameObject_->getType() == "HeadQuarters")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/headquarters.png"));
    }
    else if (gameObject_->getType() == "Outpost")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/outpost.png"));
    }
    else if (gameObject_->getType() == "Forest")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/forest.png"));
    }
    else if (gameObject_->getType() == "Grassland")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/grassland.png"));
    }
    else if (gameObject_->getType() == "Mountain")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/mountain.png"));
    }
    else if (gameObject_->getType() == "Water")
    {

        painter->drawImage(boundingRect(),  QImage(":/images/water.png"));
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
