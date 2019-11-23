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
    // Yritin saada että työkkäri ois neliössä alempana kuin HQ
    if(gameObject_->getType() == "Tyokkari")
    {
        addToPoint = QPoint(1, 0);
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
//    if ( m_gameobject->getType() == "" ){
//        // Draw different types in different shapes
//    }
//    if (gameObject_->getType() == "Tyokkari") {
//        QRectF rect = boundingRect();
//        QImage image(":/Images/worker.png");
//        QPixmap pix = QPixmap::fromImage(image);
//        brush = QBrush(pix);
//        painter->setBrush(brush);
//        painter->drawPixmap(scenelocation_.x() * 50, scenelocation_.y() * 50, pix );
//    } else {
    painter->drawRect(boundingRect());
//    }

}

std::shared_ptr<Course::GameObject> MapItem::getBoundObject()
{
    return gameObject_;
}


}
