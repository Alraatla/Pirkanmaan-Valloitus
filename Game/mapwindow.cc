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
                     SLOT(mapSetup(int)));
    connect(m_ui->pushButton, &QPushButton::clicked, this, &MapWindow::gameLoop);
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


    int itPlayersTurn = turn_ % playercount_;

    std::vector<std::shared_ptr<Team::PlayerObject>> players = m_GEHandler->getPlayers();
    MapWindow::updateHUD(players.at(itPlayersTurn));
    turn_++;
    if (itPlayersTurn == playercount_ - 1) {
        round_++;
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

void MapWindow::updateHUD(std::shared_ptr<Team::PlayerObject> player)
{
    Course::ResourceMapDouble resources = player->getResources();

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

    if(player->hasHQ()) {
        m_ui->hqButton->setDisabled(true);
    } else {
        m_ui->tyokkariButton->setDisabled(true);
        m_ui->farmButton->setDisabled(true);
        m_ui->mineButton->setDisabled(true);
        m_ui->outpostButton->setDisabled(true);
    }

}
void MapWindow::mapSetup(int playercount)
{

    m_GEHandler->setPlayercount(playercount);
    playercount_ = playercount;

    Course::WorldGenerator& world = Course::WorldGenerator::getInstance();
    world.addConstructor<Course::Forest>(1);
    world.addConstructor<Course::Grassland>(1);
    world.generateMap(10, 10, 2, m_Object, m_GEHandler);


    for(auto object: m_Object->getTilesForMap()) {
        MapWindow::drawItem(object);
    }
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
