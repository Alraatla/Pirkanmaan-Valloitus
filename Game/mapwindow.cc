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
    MapWindow::updateHUD(players.at(itPlayersTurn), round_);
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

void MapWindow::updateHUD(std::shared_ptr<Team::PlayerObject> player, int turn)
{
    Course::ResourceMapDouble resources = player->getResources();
    QString hudText = "Round: " + QString::number(turn) + "\n"
            + "Player: " + QString::fromStdString(player->getName()) + "\n"
            + "Money: " + QString::number(resources.at(Course::MONEY)) + "\n";
    m_ui->roundLabel->setText("Round: "+ QString::number(round_));
    m_ui->playerTurnLabel->setText("Player in turn: " + QString::fromStdString(player->getName()));

    m_ui->moneyAmountLabel->setText(QString::number(resources.at(Course::MONEY)));
    m_ui->foodAmountLabel->setText(QString::number(resources.at(Course::FOOD)));
    m_ui->woodAmountLabel->setText(QString::number(resources.at(Course::WOOD)));
    m_ui->stoneAmountLabel->setText(QString::number(resources.at(Course::STONE)));
    m_ui->oreAmountLabel->setText(QString::number(resources.at(Course::ORE)));

    m_ui->workerLabel->setText("Workers: " + QString::number(player->getWorkerAmount("WORKER")));
    m_ui->farmerLabel->setText("Farmers: " + QString::number(player->getWorkerAmount("FARMER")));
    m_ui->minerLabel->setText("Miners: " + QString::number(player->getWorkerAmount("MINER")));

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
