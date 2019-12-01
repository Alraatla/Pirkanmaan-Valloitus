#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <map>

#include "interfaces/igameeventhandler.h"
#include "gameeventhandler.h"
#include "objectmanager.h"
#include "graphics/simplegamescene.h"
#include "gamemenu.h"
#include "endscreen.h"
#include "gamescene.h"
#include "buildings/farm.h"
#include "buildings/outpost.h"
#include "mine.h"
#include "workers/basicworker.h"
#include "miner.h"
#include "farmer.h"

namespace Ui {
class MapWindow;
}
class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();

    void setGEHandler(std::shared_ptr<Team::GameEventHandler> nHandler);



    void setSize(int width, int height);
    void setScale(int scale);
    void resize();

    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief Updates the hud for the player
     * @param player Pointer to the player who's information is being displayed
     */
    void updateHUD(std::shared_ptr<Team::PlayerObject> player);

    /**
     * @brief sets HQs into corners of the map before the game starts.
     */
    void setHQs();

    std::shared_ptr<Team::PlayerObject> getPlayerInTurn();

    /**
     * @brief updates the available buttons to the player based on clicked tile's
     * coordinate, player resources, available workers and buildings.
     * Sorry for the mess.
     * @param coordinate Clicked coordinate from gameScene
     */
    void updateButtons(Course::Coordinate coordinate);

    /**
     * @brief Checks if the game has been won or if it has ended
     * @return Pointer to the winning player,
     * nullptr if the game is not over
     */
    std::shared_ptr<Team::PlayerObject> hasGameBeenWon();

    /**
     * @brief Executes endScreen with winning players information.
     * @param player Pointer to the winning player.
     */
    void gameEnd(std::shared_ptr<Team::PlayerObject> player);

public slots:

    /**
     * @brief Generates the map, decides the game mode, and draws tiles onto
     * the map
     * @param playercount NO. of players playing
     * @param playerNames vector of player names
     * @param winConditionIsPoints bool on if the game is decided by point
     * limit or round limit
     * @param pointsOrRounds amount of points or rounds that decide the game
     */
    void mapSetup(int playercount, std::vector<std::string> playerNames,
                  bool winConditionIsPoints, int pointsOrRounds);

    /**
     * @brief gameLoop is called every time the turn changes. It keeps track
     * of the player in turn and calls the update of hud and buttons.
     */
    void gameLoop();

    /**
     * @brief Spawns a QMessageBox with info on the game.
     */
    void infoButtonClicked();

    /**
     * @brief adds työkkäri to the player currently in turn
     */
    void tyokkariButtonClicked();

    /**
     * @brief adds farm to the player currently in turn
     */
    void farmButtonClicked();

    /**
     * @brief adds mine to the player currently in turn
     */
    void mineButtonClicked();

    /**
     * @brief adds outpost to the player currently in turn
     */
    void outpostButtonClicked();

    /**
     * @brief adds 1 available worker to the current players' workersMap_
     */
    void workerBuyButtonClicked();

    /**
     * @brief adds 1 available farmer to the current players' workersMap_
     */
    void farmerBuyButtonClicked();

    /**
     * @brief adds 1 available miner to the current players' workersMap_
     */
    void minerBuyButtonClicked();

    /**
     * @brief assigns 1 worker to the selected tile
     */
    void workerAssignButtonClicked();

    /**
     * @brief assigns 1 farmer to the selected farm
     */
    void farmerAssignButtonClicked();

    /**
     * @brief assigns 1 miner to the selected mine
     */
    void minerAssignButtonClicked();

    /**
     * @brief used to rececive information on clicked tile
     */
    void receiveSignal();

signals:

    /**
     * @brief used to emit winner to end screen
     */
    void playerObject(std::shared_ptr<Team::PlayerObject> player, int round);

private:
    Ui::MapWindow* m_ui;
    std::shared_ptr<Team::GameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<Team::GameScene> m_gamescene = nullptr;
    std::shared_ptr<Team::ObjectManager> m_ObjMgr = nullptr;
    Gamemenu* m_gamemenu;
    EndScreen* m_endscreen;
    bool winConditionIsPoints_ = true;
    int pointLimit_ = 0;
    int roundLimit_ = 0;
    int turn_ = 0;
    int playercount_ = 0;
    int round_ = 1;
};

#endif // MapWINDOW_HH

