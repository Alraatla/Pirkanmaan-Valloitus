#ifndef GAMESCENE_H
#define GAMESCENE_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <map>
#include <memory>

#include "core/gameobject.h"
#include "graphics/simplegamescene.h"

namespace Team {



class GameScene : public Course::SimpleGameScene
{
public:
    GameScene(QWidget *parent = nullptr,
              int width = 10,
              int height = 10,
              int scale = 50);
    ~GameScene() = default;

    bool event(QEvent* event);

    Course::Coordinate getClickedCoordinate();

private:
    Course::Coordinate clickedCoordinate_ = {0, 0};
};

} //

#endif // GAMESCENE_H
