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
#include "gamescene.h"
#include "buildings/farm.h"
#include "buildings/outpost.h"
#include "mine.h"
#include "workers/basicworker.h"

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
    void updateHUD(std::shared_ptr<Team::PlayerObject> player);
    void setHQs();
    void addWorker();

    std::shared_ptr<Team::PlayerObject> getPlayerInTurn();
    void updateButtons(Course::Coordinate coordinate);

public slots:

    void mapSetup(int playercount, std::vector<std::string> playerNames);
    void gameLoop();
    void hqButtonClicked();
    void tyokkariButtonClicked();
    void farmButtonClicked();
    void mineButtonClicked();
    void outpostButtonClicked();
    void workerBuyButtonClicked();
    void receiveSignal();


private:
    Ui::MapWindow* m_ui;
    std::shared_ptr<Team::GameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<Team::GameScene> m_simplescene = nullptr;
    std::shared_ptr<Team::ObjectManager> m_Object = nullptr;
    Gamemenu* m_gamemenu;
    int turn_ = 0;
    int playercount_ = 0;
    int round_ = 1;
};

#endif // MapWINDOW_HH

