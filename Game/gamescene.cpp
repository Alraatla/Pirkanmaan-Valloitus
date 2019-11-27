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
            emit tileClicked();
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

    if(obj->getType() == "Tyokkari" ||
            obj->getType() == "HeadQuarters" ||
            obj->getType() == "Mine" ||
            obj->getType() == "Outpost" ||
            obj->getType() == "Farm")
    {
        nItem = new MapItem(obj, 35);
    }
    else if (obj->getType() == "BasicWorker" ||
             obj->getType() == "Farmer" ||
             obj->getType() == "Miner")
    {
        nItem = new MapItem(obj, 20);
    }
    else
    {
        nItem = new MapItem(obj, 50);
    }





    addItem(nItem);



}




}
