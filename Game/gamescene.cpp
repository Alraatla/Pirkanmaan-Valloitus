#include "gamescene.h"
#include "graphics/simplemapitem.h"
#include "mapitem.h"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include <math.h>

namespace Team {


GameScene::GameScene(QWidget* parent,
                     int width,
                     int height,
                     int scale):
    Course::SimpleGameScene(parent, width,
                            height, scale)
{

}

bool GameScene::event(QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneMousePress)
    {
        QGraphicsSceneMouseEvent* mouse_event =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        if ( sceneRect().contains(mouse_event->scenePos())){

            QPointF point = mouse_event->scenePos() / getScale();

            point.rx() = floor(point.rx());
            point.ry() = floor(point.ry());

            QGraphicsItem* pressed = itemAt(point * getScale(), QTransform());

            clickedCoordinate_ = static_cast<Course::SimpleMapItem*>(pressed)->getBoundObject()->getCoordinate();
            qDebug() << clickedCoordinate_.x() << clickedCoordinate_.y();
            emitSignal();
            return true;


        }
    }
    return false;
}

Course::Coordinate GameScene::getClickedCoordinate()
{
    return clickedCoordinate_;
}

void GameScene::drawItem(std::shared_ptr<Course::GameObject> obj)
{
    MapItem* nItem = nullptr;
    if (obj->getType() == "HeadQuarters")
    {
        nItem = new MapItem(obj, 50);

    }
    else if (obj->getType() == "Tyokkari")
    {
        nItem = new MapItem(obj, 50);
    }
    else
    {
        nItem = new MapItem(obj, 50);
    }

    addItem(nItem);
}

void GameScene::emitSignal()
{
    emit tileClicked(clickedCoordinate_);

}


}
