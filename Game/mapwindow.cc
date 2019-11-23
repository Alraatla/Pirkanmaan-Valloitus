#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "gameeventhandler.h"
#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "mountain.h"
#include "buildings/headquarters.h"
#include "gamescene.h"
#include "tyokkari.h"

#include "graphics/simplemapitem.h"

#include <math.h>

MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(std::make_shared<Team::GameEventHandler>()),
    m_simplescene(new Team::GameScene(this)),
    m_Object(std::make_shared<Team::ObjectManager>())
{
    m_ui->setupUi(this);

    m_gamemenu = new Gamemenu;

    connect(m_gamemenu, SIGNAL(initializeGame(int, std::vector<std::string>)), this,
                     SLOT(mapSetup(int, std::vector<std::string>)));
    connect(m_ui->pushButton, &QPushButton::clicked, this, &MapWindow::gameLoop);
    //connect(m_ui->hqButton, &QPushButton::clicked, this, &MapWindow::hqButtonClicked);
    connect(m_ui->tyokkariButton, &QPushButton::clicked, this, &MapWindow::tyokkariButtonClicked);
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

void MapWindow::gameLoop()
{
    m_ui->pushButton->setText("Next turn");
    int itPlayersTurn = turn_ % playercount_;

    std::vector<std::shared_ptr<Team::PlayerObject>> players = m_GEHandler->getPlayers();
    MapWindow::updateHUD(players.at(itPlayersTurn));
    turn_++;
    if (itPlayersTurn == playercount_ - 1) {
        m_ui->pushButton->setText("End round");
        round_++;
    }


}

void MapWindow::hqButtonClicked()
{
    std::shared_ptr<Team::PlayerObject> playerInTurn = m_GEHandler->getPlayers().at(
                    (turn_-1) % playercount_);


    //m_ui->hqButton->setDisabled(false);

    std::shared_ptr<Course::HeadQuarters> headquarters = std::make_shared<Course::HeadQuarters>(
                m_GEHandler, m_Object, playerInTurn);

    std::shared_ptr<Course::TileBase> tile =
            m_Object->getTile(m_simplescene->getClickedCoordinate());

    if(tile->hasSpaceForBuildings(headquarters->spacesInTileCapacity()))
    {
        headquarters->setCoordinate(m_simplescene->getClickedCoordinate());
        tile->addBuilding(headquarters);
        MapWindow::drawItem(headquarters);
        playerInTurn->addObject(headquarters);
        m_GEHandler->addObjectToPlayer(playerInTurn, headquarters->getType());
    }

    updateHUD(playerInTurn);
}

void MapWindow::tyokkariButtonClicked()
{
    std::shared_ptr<Team::PlayerObject> playerInTurn = m_GEHandler->getPlayers().at(
                    (turn_-1) % playercount_);

    std::shared_ptr<Team::Tyokkari> tyokkari = std::make_shared<Team::Tyokkari>(
                m_GEHandler, m_Object, playerInTurn);


    std::shared_ptr<Course::TileBase> tile =
            m_Object->getTile(m_simplescene->getClickedCoordinate());

    if(tile->hasSpaceForBuildings(tyokkari->spacesInTileCapacity()))
    {
        tyokkari->setCoordinate(m_simplescene->getClickedCoordinate());
        tile->addBuilding(tyokkari);
        MapWindow::drawItem(tyokkari);
        playerInTurn->addObject(tyokkari);
        m_GEHandler->addObjectToPlayer(playerInTurn, tyokkari->getType());
    }

    updateHUD(playerInTurn);

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

void MapWindow::updateHUD(std::shared_ptr<Team::PlayerObject> player)
{
    Course::ResourceMap resources = player->getResources();

    m_ui->roundAmountLabel->setText(QString::number(round_));
    m_ui->playerNameLabel->setText(QString::fromStdString(player->getName()));
    m_ui->pointsAmountLabel->setText(QString::number(player->getPoints()));

    m_ui->moneyAmountLabel->setText(QString::number(resources.at(Course::MONEY)));
    m_ui->foodAmountLabel->setText(QString::number(resources.at(Course::FOOD)));
    m_ui->woodAmountLabel->setText(QString::number(resources.at(Course::WOOD)));
    m_ui->stoneAmountLabel->setText(QString::number(resources.at(Course::STONE)));
    m_ui->oreAmountLabel->setText(QString::number(resources.at(Course::ORE)));

    m_ui->workerAmountLabel->setText(QString::number(player->getWorkerAmount("WORKER")));
    m_ui->farmerAmountLabel->setText(QString::number(player->getWorkerAmount("FARMER")));
    m_ui->minerAmountLabel->setText(QString::number(player->getWorkerAmount("MINER")));

    if (player->hasTyokkari())
    {
        //m_ui->hqButton->setDisabled(true);
        m_ui->tyokkariButton->setDisabled(true);

        m_ui->farmButton->setDisabled(false);
        m_ui->mineButton->setDisabled(false);
        m_ui->outpostButton->setDisabled(false);
    }
    else if(player->hasHQ())
    {
        //m_ui->hqButton->setDisabled(true);
        m_ui->tyokkariButton->setDisabled(false);
    }
    else
    {
        //m_ui->hqButton->setDisabled(false);
        m_ui->tyokkariButton->setDisabled(true);
        m_ui->farmButton->setDisabled(true);
        m_ui->mineButton->setDisabled(true);
        m_ui->outpostButton->setDisabled(true);

        m_ui->workerAssignButton->setDisabled(true);
        m_ui->workerBuyButton->setDisabled(true);

        m_ui->farmerAssignButton->setDisabled(true);
        m_ui->farmerBuyButton->setDisabled(true);

        m_ui->minerAssignButton->setDisabled(true);
        m_ui->minerBuyButton->setDisabled(true);

    }

}

void MapWindow::setHQs()
{
    std::pair<int, int> mapSize = m_simplescene->getSize();
    std::vector<std::shared_ptr<Team::PlayerObject>> players = m_GEHandler->getPlayers();
    std::vector<std::pair<int, int>> hqPlaces = {{0, 0},
                                                 {mapSize.first - 1, mapSize.second-1},
                                                 {mapSize.first - 1, 0},
                                                 {0, mapSize.second-1}};
    for(int i=0; i< players.size(); i++) {
        std::shared_ptr<Course::HeadQuarters> headquarters = std::make_shared<Course::HeadQuarters>(
                    m_GEHandler, m_Object, players.at(i));

        std::pair<int, int> hqPair = hqPlaces.at(i);
        Course::Coordinate hqCoordinate = Course::Coordinate(hqPair.first, hqPair.second);
        players.at(i)->addOwnedTiles(hqCoordinate, 4, mapSize, m_Object);

        std::shared_ptr<Course::TileBase> tile =
                m_Object->getTile(Course::Coordinate(hqCoordinate));
        headquarters->setCoordinate(hqCoordinate);
        tile->addBuilding(headquarters);
        MapWindow::drawItem(headquarters);
        players.at(i)->addObject(headquarters);
        m_GEHandler->addObjectToPlayer(players.at(i), headquarters->getType());
    }
}

void MapWindow::addWorker()
{

}


void MapWindow::mapSetup(int playercount, std::vector<std::string> playerNames)
{

    //m_ui->hqButton->setDisabled(true);
    m_ui->tyokkariButton->setDisabled(true);
    m_ui->farmButton->setDisabled(true);
    m_ui->mineButton->setDisabled(true);
    m_ui->outpostButton->setDisabled(true);

    m_ui->workerAssignButton->setDisabled(true);
    m_ui->workerBuyButton->setDisabled(true);

    m_ui->farmerAssignButton->setDisabled(true);
    m_ui->farmerBuyButton->setDisabled(true);

    m_ui->minerAssignButton->setDisabled(true);
    m_ui->minerBuyButton->setDisabled(true);


    m_GEHandler->setPlayercount(playercount, playerNames);
    playercount_ = playercount;



    Course::WorldGenerator& world = Course::WorldGenerator::getInstance();
    world.addConstructor<Course::Forest>(2);
    world.addConstructor<Course::Grassland>(2);
    world.addConstructor<Team::Mountain>(1);
    world.generateMap(10, 10, 1231524123, m_Object, m_GEHandler);


    for(auto object: m_Object->getTilesForMap()) {
        MapWindow::drawItem(object);
    }
    setHQs();

}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
    m_ui->graphicsView->viewport()->update();
}
