#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "gameeventhandler.h"
#include "core/worldgenerator.h"

#include "graphics/simplemapitem.h"

#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_simplescene(new Course::SimpleGameScene(this))
{
    m_ui->setupUi(this);

    m_gamemenu = new Gamemenu;

    connect(m_gamemenu, SIGNAL(initializeGame(int)), this,
                     SLOT(setPlayerCount(int)));
    m_gamemenu->exec();



    auto ptr = std::make_shared<Team::gameEventHandler>();

    m_OManager = std::make_shared<Team::objectManager>();

    setGEHandler(ptr);

    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
}

void MapWindow::setPlayerCount(int playercount)
{
    /*
    Setting the player count and testing that the signal works.
    */
    playercount_ = playercount;
    QString text = "Player count: " + QString::number(playercount);
    m_simplescene->addText(text);
    auto world = std::make_shared<Course::WorldGenerator>();
    world->addConstructor(Forest);
    world->addConstructor<Grassland>(2);
    world->generateMap(50, 50, 2, m_OManager, m_GEHandler);



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
