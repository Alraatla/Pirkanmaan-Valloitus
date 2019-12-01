#include <QDebug>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <QTimer>

#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "mountain.h"
#include "water.h"
#include "buildings/headquarters.h"
#include "gamescene.h"
#include "tyokkari.h"
#include "endscreen.h"


MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(std::make_shared<Team::GameEventHandler>()),
    m_gamescene(new Team::GameScene(this)),
    m_ObjMgr(std::make_shared<Team::ObjectManager>())
{
    m_ui->setupUi(this);

    m_gamemenu = new Gamemenu;

    connect(m_gamemenu, SIGNAL(initializeGame(int, std::vector<std::string>, bool, int)), this,
                     SLOT(mapSetup(int, std::vector<std::string>, bool, int)));

    connect(m_ui->pushButton, &QPushButton::clicked, this,
            &MapWindow::gameLoop);
    connect(m_ui->tyokkariButton, &QPushButton::clicked, this,
            &MapWindow::tyokkariButtonClicked);
    connect(m_ui->farmButton, &QPushButton::clicked, this,
            &MapWindow::farmButtonClicked);
    connect(m_ui->mineButton, &QPushButton::clicked, this,
            &MapWindow::mineButtonClicked);
    connect(m_ui->outpostButton, &QPushButton::clicked, this,
            &MapWindow::outpostButtonClicked);

    connect(m_ui->workerBuyButton, &QPushButton::clicked, this,
            &MapWindow::workerBuyButtonClicked);
    connect(m_ui->farmerBuyButton, &QPushButton::clicked, this,
            &MapWindow::farmerBuyButtonClicked);
    connect(m_ui->minerBuyButton, &QPushButton::clicked, this,
            &MapWindow::minerBuyButtonClicked);

    connect(m_ui->workerAssignButton, &QPushButton::clicked, this,
            &MapWindow::workerAssignButtonClicked);
    connect(m_ui->farmerAssignButton, &QPushButton::clicked, this,
            &MapWindow::farmerAssignButtonClicked);
    connect(m_ui->minerAssignButton, &QPushButton::clicked, this,
            &MapWindow::minerAssignButtonClicked);

    Course::SimpleGameScene* sgs_rawptr = m_gamescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    connect(sgs_rawptr, SIGNAL(tileClicked()), this, SLOT(receiveSignal()));

    // MapWindow closes when dialog window cancel button is pressed
    if(m_gamemenu->exec() == QDialog::Rejected)
    {
        QTimer::singleShot(0, this, SLOT(close()));
    }
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
    if(turn_ > 0)
    {
        std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();
        m_GEHandler->modifyResourcesAtTurnEnd(playerInTurn);
    }

    int itPlayersTurn = turn_ % playercount_;

    m_ui->pushButton->setText("Next player");
    std::vector<std::shared_ptr<Team::PlayerObject>> players =
            m_GEHandler->getPlayers();

    if(hasGameBeenWon() == nullptr)
    {
        MapWindow::updateHUD(players.at(itPlayersTurn));
        turn_++;
        if (itPlayersTurn == playercount_ - 1)
        {
            m_ui->pushButton->setText("Next round");
            round_++;
        }
    }
    else
    {
        gameEnd(hasGameBeenWon());
    }
}

void MapWindow::tyokkariButtonClicked()
{

    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();

    std::shared_ptr<Team::Tyokkari> tyokkari = std::make_shared<Team::Tyokkari>(
                m_GEHandler, m_ObjMgr, playerInTurn);


    std::shared_ptr<Course::TileBase> tile =
            m_ObjMgr->getTile(m_gamescene->getClickedCoordinate());

    if(tile->hasSpaceForBuildings(tyokkari->spacesInTileCapacity()))
    {
        tyokkari->setCoordinate(m_gamescene->getClickedCoordinate());
        tile->addBuilding(tyokkari);
        MapWindow::drawItem(tyokkari);
        playerInTurn->addObject(tyokkari);
        m_GEHandler->addObjectToPlayer(playerInTurn, tyokkari->getType());
    }

    updateHUD(playerInTurn);

}

void MapWindow::farmButtonClicked()
{
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();

    std::shared_ptr<Course::Farm> farm = std::make_shared<Course::Farm>(
                m_GEHandler, m_ObjMgr, playerInTurn);


    std::shared_ptr<Course::TileBase> tile =
            m_ObjMgr->getTile(m_gamescene->getClickedCoordinate());

    if(tile->hasSpaceForBuildings(farm->spacesInTileCapacity()))
    {
        farm->setCoordinate(m_gamescene->getClickedCoordinate());
        tile->addBuilding(farm);
        MapWindow::drawItem(farm);
        playerInTurn->addObject(farm);
        m_GEHandler->addObjectToPlayer(playerInTurn, farm->getType());
    }

    updateHUD(playerInTurn);
}

void MapWindow::mineButtonClicked()
{
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();

    std::shared_ptr<Team::Mine> mine = std::make_shared<Team::Mine>(
                m_GEHandler, m_ObjMgr, playerInTurn);


    std::shared_ptr<Course::TileBase> tile =
            m_ObjMgr->getTile(m_gamescene->getClickedCoordinate());

    if(tile->hasSpaceForBuildings(mine->spacesInTileCapacity()))
    {
        mine->setCoordinate(m_gamescene->getClickedCoordinate());
        tile->addBuilding(mine);
        MapWindow::drawItem(mine);
        playerInTurn->addObject(mine);
        m_GEHandler->addObjectToPlayer(playerInTurn, mine->getType());
    }

    updateHUD(playerInTurn);
}

void MapWindow::outpostButtonClicked()
{
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();

    std::shared_ptr<Course::Outpost> outpost = std::make_shared<Course::Outpost>(
                m_GEHandler, m_ObjMgr, playerInTurn);


    std::shared_ptr<Course::TileBase> tile =
            m_ObjMgr->getTile(m_gamescene->getClickedCoordinate());

    if(tile->hasSpaceForBuildings(outpost->spacesInTileCapacity()))
    {
        outpost->setCoordinate(m_gamescene->getClickedCoordinate());
        tile->addBuilding(outpost);
        MapWindow::drawItem(outpost);
        playerInTurn->addObject(outpost);
        m_GEHandler->addObjectToPlayer(playerInTurn, outpost->getType());
    }
    getPlayerInTurn()->addOwnedTiles(m_gamescene->getClickedCoordinate(), 2,
                                     m_gamescene->getSize(), m_ObjMgr);
    updateHUD(playerInTurn);
}

void MapWindow::workerBuyButtonClicked()
{
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();

    std::shared_ptr<Course::BasicWorker> worker = std::make_shared<Course::BasicWorker>(
                m_GEHandler, m_ObjMgr, playerInTurn);

    playerInTurn->addObject(worker);
    playerInTurn->addWorker("WORKERS");
    m_ObjMgr->addWorker(worker);
    m_GEHandler->addObjectToPlayer(playerInTurn, worker->getType());
    updateHUD(playerInTurn);
}

void MapWindow::farmerBuyButtonClicked()
{
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();

    std::shared_ptr<Team::Farmer> farmer = std::make_shared<Team::Farmer>(
                m_GEHandler, m_ObjMgr, playerInTurn);

    playerInTurn->addObject(farmer);
    playerInTurn->addWorker("FARMERS");
    m_ObjMgr->addWorker(farmer);
    m_GEHandler->addObjectToPlayer(playerInTurn, farmer->getType());
    updateHUD(playerInTurn);
}

void MapWindow::minerBuyButtonClicked()
{
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();

    std::shared_ptr<Team::Miner> miner = std::make_shared<Team::Miner>(
                m_GEHandler, m_ObjMgr, playerInTurn);

    playerInTurn->addObject(miner);
    playerInTurn->addWorker("MINERS");
    m_ObjMgr->addWorker(miner);
    m_GEHandler->addObjectToPlayer(playerInTurn, miner->getType());
    updateHUD(playerInTurn);
}

void MapWindow::workerAssignButtonClicked()
{
    std::shared_ptr<Course::TileBase> tile =
            m_ObjMgr->getTile(m_gamescene->getClickedCoordinate());
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();
    std::shared_ptr<Course::WorkerBase> worker =
            playerInTurn->getWorker("BasicWorker",
                                    m_ObjMgr->getPlayersWorkers(playerInTurn));
    tile->setOwner(playerInTurn);
    tile->addWorker(worker);
    playerInTurn->workerAssigned("WORKERS");
    drawItem(worker);
    updateHUD(playerInTurn);
}

void MapWindow::farmerAssignButtonClicked()
{
    std::shared_ptr<Course::TileBase> tile =
            m_ObjMgr->getTile(m_gamescene->getClickedCoordinate());
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();
    std::shared_ptr<Course::WorkerBase> farmer =
            playerInTurn->getWorker("Farmer",
                                    m_ObjMgr->getPlayersWorkers(playerInTurn));
    tile->setOwner(playerInTurn);
    tile->addWorker(farmer);
    playerInTurn->workerAssigned("FARMERS");
    drawItem(farmer);
    updateHUD(playerInTurn);
}

void MapWindow::minerAssignButtonClicked()
{
    std::shared_ptr<Course::TileBase> tile =
            m_ObjMgr->getTile(m_gamescene->getClickedCoordinate());
    std::shared_ptr<Team::PlayerObject> playerInTurn = getPlayerInTurn();
    std::shared_ptr<Course::WorkerBase> miner =
            playerInTurn->getWorker("Miner",
                                    m_ObjMgr->getPlayersWorkers(playerInTurn));
    tile->setOwner(playerInTurn);
    tile->addWorker(miner);
    playerInTurn->workerAssigned("MINERS");
    drawItem(miner);
    updateHUD(playerInTurn);
}

void MapWindow::receiveSignal()
{
    updateButtons(m_gamescene->getClickedCoordinate());
}

void MapWindow::updateButtons(Course::Coordinate coordinate)
{
    if(turn_ != 0)
    {
        std::shared_ptr<Team::PlayerObject> player = getPlayerInTurn();

        if(player->isTileOwned(coordinate))
        {
            std::shared_ptr<Course::TileBase> tile = m_ObjMgr->getTile(coordinate);

            if(tile->getBuildingCount() > 0)
            {
                // Disable kaikki rakennus nappulat
                std::string building = tile->getBuildings().at(0)->getType();
                if(building == "Tyokkari")
                {
                //case "Tyokkari":

                    if(player->hasEnoughResourcesFor(Course::ConstResourceMaps::BW_RECRUITMENT_COST))
                    {
                        m_ui->workerBuyButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->workerBuyButton->setEnabled(false);
                    }
                    if(player->hasEnoughResourcesFor(Team::TeamConstResourceMaps::FARMER_RECRUITMENT_COST))
                    {
                        m_ui->farmerBuyButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->farmerBuyButton->setEnabled(false);
                    }
                    if(player->hasEnoughResourcesFor(Team::TeamConstResourceMaps::MINER_RECRUITMENT_COST))
                    {
                        m_ui->minerBuyButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->minerBuyButton->setEnabled(false);
                    }

                    m_ui->workerAssignButton->setEnabled(false);
                    m_ui->farmerAssignButton->setEnabled(false);
                    m_ui->minerAssignButton->setEnabled(false);
                }
                else if(building == "Farm")
                {
                    //case "Farm":
                    if(player->getWorkerAmount("FARMERS") > 0 &&
                            tile->getWorkerCount() == 0){
                        m_ui->farmerAssignButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->farmerAssignButton->setEnabled(false);
                    }

                    m_ui->workerBuyButton->setEnabled(false);
                    m_ui->workerAssignButton->setEnabled(false);
                    m_ui->farmerBuyButton->setEnabled(false);
                    m_ui->minerBuyButton->setEnabled(false);
                    m_ui->minerAssignButton->setEnabled(false);


                }
                    // farmerin töihi nappi jos farm,ereiden lkm > 0
                else if(building == "Mine")
                {
                    //case "Mine":
                    if(player->getWorkerAmount("MINERS") > 0 &&
                            tile->getWorkerCount() == 0)
                    {
                        m_ui->minerAssignButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->minerAssignButton->setEnabled(false);
                    }

                    m_ui->workerBuyButton->setEnabled(false);
                    m_ui->workerAssignButton->setEnabled(false);
                    m_ui->minerBuyButton->setEnabled(false);
                    m_ui->farmerBuyButton->setEnabled(false);
                    m_ui->farmerAssignButton->setEnabled(false);
                }
                else
                {
                    // case default:
                    m_ui->workerBuyButton->setEnabled(false);
                    m_ui->workerAssignButton->setEnabled(false);
                    m_ui->farmerBuyButton->setEnabled(false);
                    m_ui->farmerAssignButton->setEnabled(false);
                    m_ui->minerBuyButton->setEnabled(false);
                    m_ui->minerAssignButton->setEnabled(false);
                }

                m_ui->tyokkariButton->setEnabled(false);
                m_ui->farmButton->setEnabled(false);
                m_ui->mineButton->setEnabled(false);
                m_ui->outpostButton->setEnabled(false);

            }
            else
            {
                // Kun klikatussa tiilessä ei ole rakennusta
                std::string tile_type = tile->getType();
                if(tile_type == "Forest")
                {
                    // voi rakentaa työkkäri ja outpost ja töihin voio tulla worker
                    if(player->hasTyokkari())
                    {
                        m_ui->tyokkariButton->setEnabled(false);
                    }
                    else if (player->hasEnoughResourcesFor(Team::TeamConstResourceMaps::TYOKKARI_BUILD_COST))
                    {
                        m_ui->tyokkariButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->tyokkariButton->setEnabled(false);
                    }

                    if(player->hasEnoughResourcesFor(Course::ConstResourceMaps::OUTPOST_BUILD_COST) &&
                            tile->getWorkerCount() == 0)
                    {
                        m_ui->outpostButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->outpostButton->setEnabled(false);
                    }
                    if(player->getWorkerAmount("WORKERS") > 0 &&
                            tile->getWorkerCount() == 0) {
                        m_ui->workerAssignButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->workerAssignButton->setEnabled(false);
                    }

                    m_ui->mineButton->setEnabled(false);
                    m_ui->farmButton->setEnabled(false);
                }
                else if(tile_type == "Mountain")
                {
                    if(player->hasEnoughResourcesFor(Team::TeamConstResourceMaps::MINE_BUILD_COST))
                    {
                        m_ui->mineButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->mineButton->setEnabled(false);
                    }
                    m_ui->tyokkariButton->setEnabled(false);
                    m_ui->farmButton->setEnabled(false);
                    m_ui->outpostButton->setEnabled(false);
                }
                else if(tile_type == "Grassland")
                {
                    // voi rakentaa työkkärin ja farmin ja töihin voi tulla worker
                    if(player->hasTyokkari())
                    {
                        m_ui->tyokkariButton->setEnabled(false);
                    }
                    else if (player->hasEnoughResourcesFor(Team::TeamConstResourceMaps::TYOKKARI_BUILD_COST))
                    {
                        m_ui->tyokkariButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->tyokkariButton->setEnabled(false);
                    }
                    // Tarkastelu ettei tiilessä ole workeria ja sitten rakennusten rakennus
                    if(tile->getWorkerCount() == 0)
                    {
                        if(player->hasEnoughResourcesFor(Course::ConstResourceMaps::OUTPOST_BUILD_COST)) {
                            m_ui->outpostButton->setEnabled(true);
                        }
                        else
                        {
                            m_ui->outpostButton->setEnabled(false);
                        }
                        if(player->hasEnoughResourcesFor(Course::ConstResourceMaps::FARM_BUILD_COST))
                        {
                            m_ui->farmButton->setEnabled(true);
                        }
                        else
                        {
                            m_ui->farmButton->setEnabled(false);
                        }
                    }
                    else
                    {
                        m_ui->tyokkariButton->setEnabled(false);
                        m_ui->farmButton->setEnabled(false);
                        m_ui->outpostButton->setEnabled(false);
                    }


                    if(player->getWorkerAmount("WORKERS") > 0 &&
                            tile->getWorkerCount() == 0) {
                        m_ui->workerAssignButton->setEnabled(true);
                    }
                    else
                    {
                        m_ui->workerAssignButton->setEnabled(false);
                    }

                    m_ui->mineButton->setEnabled(false);
                }
                else if (tile_type == "Water")
                {
                    m_ui->tyokkariButton->setEnabled(false);
                    m_ui->farmButton->setEnabled(false);
                    m_ui->outpostButton->setEnabled(false);
                    m_ui->mineButton->setEnabled(false);
                }

                m_ui->workerBuyButton->setEnabled(false);
                m_ui->farmerBuyButton->setEnabled(false);
                m_ui->farmerAssignButton->setEnabled(false);
                m_ui->minerBuyButton->setEnabled(false);
                m_ui->minerAssignButton->setEnabled(false);
            }
        }
        else
        {
            m_ui->workerBuyButton->setEnabled(false);
            m_ui->workerAssignButton->setEnabled(false);
            m_ui->farmerBuyButton->setEnabled(false);
            m_ui->farmerAssignButton->setEnabled(false);
            m_ui->minerBuyButton->setEnabled(false);
            m_ui->minerAssignButton->setEnabled(false);

            m_ui->tyokkariButton->setEnabled(false);
            m_ui->outpostButton->setEnabled(false);
            m_ui->farmButton->setEnabled(false);
            m_ui->mineButton->setEnabled(false);
        }
    }
}

std::shared_ptr<Team::PlayerObject> MapWindow::hasGameBeenWon()
{
    std::vector<std::shared_ptr<Team::PlayerObject>> players =
            m_GEHandler->getPlayers();
    if(winConditionIsPoints_)
    {
        for(std::shared_ptr<Team::PlayerObject> player : players)
        {
            if(player->getPoints() >= pointLimit_)
            {
                return player;
            }
        }
    }
    else
    {
        if(round_ > roundLimit_)
        {
            int mostPoints = 0;
            std::shared_ptr<Team::PlayerObject> playerWithMostPoints = nullptr;
            for(std::shared_ptr<Team::PlayerObject> player : players)
            {
                if(player->getPoints() > mostPoints)
                {
                    playerWithMostPoints = player;
                    mostPoints = player->getPoints();
                }
            }
            return playerWithMostPoints;
        }
    }
    return nullptr;
}

void MapWindow::gameEnd(std::shared_ptr<Team::PlayerObject> player)
{
    m_endscreen = new EndScreen(this);
    emit playerObject(player, round_);
    m_endscreen->exec();

    this->close();
}

void MapWindow::setSize(int width, int height)
{
    m_gamescene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_gamescene->setScale(scale);
}

void MapWindow::resize()
{
    m_gamescene->resize();
}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_gamescene->updateItem(obj);
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



    m_ui->workerAmountLabel->setText(QString::number(player->getWorkerAmount("WORKERS")));
    m_ui->farmerAmountLabel->setText(QString::number(player->getWorkerAmount("FARMERS")));
    m_ui->minerAmountLabel->setText(QString::number(player->getWorkerAmount("MINERS")));

    updateButtons(m_gamescene->getClickedCoordinate());
    m_ui->graphicsView->fitInView(m_gamescene->sceneRect(), Qt::KeepAspectRatio);
}

void MapWindow::setHQs()
{
    std::pair<int, int> mapSize = m_gamescene->getSize();
    std::vector<std::shared_ptr<Team::PlayerObject>> players = m_GEHandler->getPlayers();
    std::vector<std::pair<int, int>> hqPlaces = {{0, 0},
                                                 {mapSize.first - 1, mapSize.second-1},
                                                 {mapSize.first - 1, 0},
                                                 {0, mapSize.second-1}};

    int vectorSize = players.size();
    for(int i = 0; i < vectorSize; i++)
    {
        std::shared_ptr<Course::HeadQuarters> headquarters =
                std::make_shared<Course::HeadQuarters>(
                    m_GEHandler, m_ObjMgr, players.at(i));

        std::pair<int, int> hqPair = hqPlaces.at(i);
        Course::Coordinate hqCoordinate = Course::Coordinate(hqPair.first, hqPair.second);
        players.at(i)->addOwnedTiles(hqCoordinate, 4, mapSize, m_ObjMgr);

        std::shared_ptr<Course::TileBase> tile =
                m_ObjMgr->getTile(Course::Coordinate(hqCoordinate));
        headquarters->setCoordinate(hqCoordinate);
        tile->addBuilding(headquarters);
        MapWindow::drawItem(headquarters);
        players.at(i)->addObject(headquarters);
        m_GEHandler->addObjectToPlayer(players.at(i), headquarters->getType());
    }
}

std::shared_ptr<Team::PlayerObject> MapWindow::getPlayerInTurn()
{
    return m_GEHandler->getPlayers().at((turn_-1) % playercount_);
}

void MapWindow::mapSetup(int playercount, std::vector<std::string> playerNames,
                         bool winConditionIsPoints, int pointsOrRounds)
{

    if(winConditionIsPoints)
    {
        pointLimit_ = pointsOrRounds;
    }
    else
    {
        roundLimit_ = pointsOrRounds;
        winConditionIsPoints_ = false;
    }
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

    setSize(12, 12);
    Course::WorldGenerator& world = Course::WorldGenerator::getInstance();
    world.addConstructor<Course::Forest>(40);
    world.addConstructor<Course::Grassland>(50);
    world.addConstructor<Team::Mountain>(10);
    world.addConstructor<Team::Water>(5);

    srand(unsigned(time(0)));
    int random = rand();
    world.generateMap(12, 12, random, m_ObjMgr, m_GEHandler);

    for(auto object: m_ObjMgr->getTilesForMap())
    {
        MapWindow::drawItem(object);
    }

    setHQs();

}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_gamescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_gamescene->drawItem(obj);
    m_ui->graphicsView->viewport()->update();
}
