#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "gameeventhandler.h"
#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"

#include "graphics/simplemapitem.h"

#include <math.h>

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(std::make_shared<Team::GameEventHandler>()),
    m_simplescene(new Course::SimpleGameScene(this)),
    m_Object(std::make_shared<Team::ObjectManager>())
{
    m_ui->setupUi(this);

    m_gamemenu = new Gamemenu;

    connect(m_gamemenu, SIGNAL(initializeGame(int)), this,
                     SLOT(setPlayerCount(int)));
    m_gamemenu->exec();

    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::setGEHandler(
        std::shared_ptr<Team::GameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
}

void MapWindow::setPlayerCount(int playercount)
{
    /*
    Setting the player count and testing that the signal works.
    */
    playercount_ = playercount;
    // Miten päästään käsiksi meidän omaan gameEvent handleriin
    m_GEHandler->setPlayercount(playercount);

    Course::WorldGenerator& world = Course::WorldGenerator::getInstance();
    world.addConstructor<Course::Forest>(1);
    world.addConstructor<Course::Grassland>(1);
    world.generateMap(5, 5, 2, m_Object, m_GEHandler);

    for(auto object: m_Object->getTilesForMap()) {
        MapWindow::drawItem(object);
    }


}

void MapWindow::setSize(int width, int height)
{
    m_simplescene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_simplescene->setScale(scale);
}

void MapWindow::resize()
{
    m_simplescene->resize();
}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->updateItem(obj);
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
