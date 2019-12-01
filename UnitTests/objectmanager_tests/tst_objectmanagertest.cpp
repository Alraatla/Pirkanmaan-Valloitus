#include <QString>
#include <QtTest>
#include <algorithm>
#include <utility>

#include "objectmanager.h"
#include "gameeventhandler.h"
#include "farmer.h"

struct testTileData
{
    Course::Coordinate coordinate = {0 , 0};
    int x;
    int y;
    Course::ObjectId id;
    std::shared_ptr<Course::TileBase> tile = nullptr;
};

class Objectmanagertest : public QObject
{
    Q_OBJECT

public:
    Objectmanagertest();

    /**
     * @brief Makes tiles like worldgenerator, with given map width
     * and height. Also stores data to testData with its given x and y
     * coordinates.
     */
    std::vector<std::shared_ptr<Course::TileBase>>
            makeTiles(int width, int height,
                      std::shared_ptr<Team::ObjectManager> objM,
                      testTileData &testData);

private Q_SLOTS:

    void testAddTiles_data();
    void testAddTiles();

    void testGetTileWithCoordinate_data();
    void testGetTileWithCoordinate();

    void testGetTileWithID_data();
    void testGetTileWithID();

    void testGetTiles_data();
    void testGetTiles();

    void testGetTilesForMap_data();
    void testGetTilesForMap();

    void testAddWorker();

    void testGetPlayersWorkers();
};

Objectmanagertest::Objectmanagertest()
{
}

std::vector<std::shared_ptr<Course::TileBase> >
Objectmanagertest::makeTiles(int width, int height,
                             std::shared_ptr<Team::ObjectManager> objM,
                             testTileData &testData)
{
    std::shared_ptr<Team::GameEventHandler> t_gameEventHandler(new Team::GameEventHandler);
    std::vector<std::shared_ptr<Course::TileBase>> tiles = {};

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            int tileX = x;
            int tileY = y;
            Course::Coordinate newCoordinate(tileX, tileY);
            std::shared_ptr<Course::TileBase> newTile =
                    std::make_shared<Course::TileBase>(newCoordinate,
                                                       t_gameEventHandler,
                                                       objM);
            tiles.push_back(newTile);
            if(testData.x == x && testData.y == y)
            {
                testData.coordinate = newCoordinate;
                testData.id = newTile->ID;
                testData.tile = newTile;
            }
        }
    }
    return tiles;
}

void Objectmanagertest::testAddTiles_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("size");
    QTest::addColumn<int>("xCoordinate");
    QTest::addColumn<int>("yCoordinate");

    QTest::newRow("Small map") << 5 << 3 << 5*3 << 0 << 0;
    QTest::newRow("No map") << 0 << 0 << 0 << 0 << 0;
    QTest::newRow("One tile") << 1 << 1 << 1*1 << 0 << 0;
    QTest::newRow("Big map") << 50 << 30 << 50*30 << 49 << 29;
}

void Objectmanagertest::testAddTiles()
{
    QFETCH(int, width);
    QFETCH(int, height);
    QFETCH(int, size);
    QFETCH(int, xCoordinate);
    QFETCH(int, yCoordinate);

    std::shared_ptr<Team::ObjectManager> t_objectManager(new Team::ObjectManager);
    testTileData testData;
    testData.x = xCoordinate;
    testData.y = yCoordinate;

    std::vector<std::shared_ptr<Course::TileBase>> tiles =
            makeTiles(width, height, t_objectManager, testData);

    t_objectManager->addTiles(tiles);

    std::vector<std::shared_ptr<Course::TileBase>> tilesFromObjMgr =
            t_objectManager->getTilesForMap();

    int vectorSize = t_objectManager->getTilesForMap().size();

    QVERIFY2(size == vectorSize, "Error, vector not right size");


    if(strcmp("No map", QTest::currentDataTag()) != 0)
    {
        QVERIFY2(std::find(tilesFromObjMgr.begin(), tilesFromObjMgr.end(),
                           testData.tile) != tilesFromObjMgr.end(),
                            "Test tile not found");
    }


}

void Objectmanagertest::testGetTileWithCoordinate_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("xCoordinate");
    QTest::addColumn<int>("yCoordinate");

    QTest::newRow("Small map, tile in corner") << 5 << 3 << 0 << 0;
    QTest::newRow("One tile") << 1 << 1 << 0 << 0;
    QTest::newRow("Big map") << 50 << 30 << 10 << 29;
}

void Objectmanagertest::testGetTileWithCoordinate()
{
    QFETCH(int, width);
    QFETCH(int, height);
    QFETCH(int, xCoordinate);
    QFETCH(int, yCoordinate);

    std::shared_ptr<Team::ObjectManager> t_objectManager(new Team::ObjectManager);
    testTileData data;
    data.x = xCoordinate;
    data.y = yCoordinate;
    std::shared_ptr<Course::TileBase> testTile = nullptr;

    std::vector<std::shared_ptr<Course::TileBase>> tiles =
            makeTiles(width, height, t_objectManager, data);

    t_objectManager->addTiles(tiles);
    testTile = t_objectManager->getTile(data.coordinate);

    QVERIFY2(testTile == data.tile, "Different tiles have same coordinate");

}

void Objectmanagertest::testGetTileWithID_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("xCoordinate");
    QTest::addColumn<int>("yCoordinate");

    QTest::newRow("Small map, tile in corner") << 5 << 3 << 0 << 0;
    QTest::newRow("One tile") << 1 << 1 << 0 << 0;
    QTest::newRow("Big map") << 50 << 30 << 10 << 29;
}

void Objectmanagertest::testGetTileWithID()
{
    QFETCH(int, width);
    QFETCH(int, height);
    QFETCH(int, xCoordinate);
    QFETCH(int, yCoordinate);

    std::shared_ptr<Team::ObjectManager> t_objectManager(new Team::ObjectManager);
    testTileData data;
    data.x = xCoordinate;
    data.y = yCoordinate;
    std::shared_ptr<Course::TileBase> testTile = nullptr;

    std::vector<std::shared_ptr<Course::TileBase>> tiles =
            makeTiles(width, height, t_objectManager, data);

    t_objectManager->addTiles(tiles);
    testTile = t_objectManager->getTile(data.id);

    QVERIFY2(testTile == data.tile, "ID matches but tile does not");
}

void Objectmanagertest::testGetTiles_data()
{
    QTest::addColumn<int>("x1");
    QTest::addColumn<int>("y1");
    QTest::addColumn<int>("x2");
    QTest::addColumn<int>("y2");
    QTest::addColumn<int>("x3");
    QTest::addColumn<int>("y3");


    QTest::newRow("Basic Vector") << 1 << 2 << 1 << 2 << 10 << 10;

    QTest::newRow("All same coordinate") << 1 << 1 << 1 << 1 << 1 << 1;

    QTest::newRow("Empty vector") << 0 << 0 << 0 << 0 << 0 << 0;
}

void Objectmanagertest::testGetTiles()
{
    QFETCH(int, x1);
    QFETCH(int, y1);
    QFETCH(int, x2);
    QFETCH(int, y2);
    QFETCH(int, x3);
    QFETCH(int, y3);

    std::vector<Course::Coordinate> coordinates;

    if(strcmp("Empty vector", QTest::currentDataTag()) != 0)
    {
        coordinates = {};
    }
    else
    {
        coordinates = {{x1, y1},
                       {x2, y2},
                       {x3, y3}};
    }

    std::shared_ptr<Team::ObjectManager> t_objectManager(new Team::ObjectManager);

    testTileData data;

    std::vector<std::shared_ptr<Course::TileBase>> tiles =
            makeTiles(20, 20, t_objectManager, data);

    t_objectManager->addTiles(tiles);
    std::vector<std::shared_ptr<Course::TileBase>> tilesFromGetTiles =
            t_objectManager->getTiles(coordinates);

    std::vector<std::shared_ptr<Course::TileBase>> tilesFromGetTile = {};
    for(Course::Coordinate coordinate : coordinates)
    {
        std::shared_ptr<Course::TileBase> tile = t_objectManager->getTile(coordinate);
        tilesFromGetTile.push_back(tile);
    }

    QVERIFY2(tilesFromGetTile.size() == tilesFromGetTiles.size(), "Vectors are not same size");


    int vectorSize = tilesFromGetTile.size();
    for(int i = 0; i < vectorSize; i++)
    {
        QVERIFY2(tilesFromGetTile.at(i) == tilesFromGetTiles.at(i), "Tiles do not match");
    }

}

void Objectmanagertest::testGetTilesForMap_data()
{
    QTest::addColumn<int>("width");
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("xCoordinate");
    QTest::addColumn<int>("yCoordinate");

    QTest::newRow("Small map, tile in corner") << 5 << 3 << 0 << 0;
    QTest::newRow("One tile") << 1 << 1 << 0 << 0;
    QTest::newRow("Empty map") << 0 << 0 << 0 << 0;
    QTest::newRow("Big map") << 50 << 30 << 10 << 29;
}

void Objectmanagertest::testGetTilesForMap()
{
    QFETCH(int, width);
    QFETCH(int, height);
    QFETCH(int, xCoordinate);
    QFETCH(int, yCoordinate);

    std::shared_ptr<Team::ObjectManager> t_objectManager(new Team::ObjectManager);
    testTileData data;
    data.x = xCoordinate;
    data.y = yCoordinate;

    std::vector<std::shared_ptr<Course::TileBase>> tiles =
            makeTiles(width, height, t_objectManager, data);

    t_objectManager->addTiles(tiles);
    std::vector<std::shared_ptr<Course::TileBase>> tilesFromObjMngr =
            t_objectManager->getTilesForMap();

    int vectorSize = tilesFromObjMngr.size();
    for(int i = 0; i < vectorSize; i++)
    {
        QVERIFY2(tiles.at(i) == tilesFromObjMngr.at(i), "Tiles do not match");
    }

    if (strcmp("Empty map", QTest::currentDataTag()) != 0)
    {
        QVERIFY2(std::count(tilesFromObjMngr.begin(), tilesFromObjMngr.end(), data.tile) > 0,
                 "Test tile not found in the vector, or there were multiple instances of it");
    }

}


void Objectmanagertest::testAddWorker()
{
    // Create a worker
    std::shared_ptr<Team::GameEventHandler> t_gameEventHandler(new Team::GameEventHandler);
    std::shared_ptr<Team::ObjectManager> t_objectManager(new Team::ObjectManager);
    std::shared_ptr<Team::PlayerObject> player(new Team::PlayerObject("Test"));

    std::shared_ptr<Team::Farmer> worker(
                new Team::Farmer(t_gameEventHandler, t_objectManager, player));

    worker->setOwner(player);
    t_objectManager->addWorker(worker);

    // Test that objectmanager still has it
    QVERIFY2(worker == t_objectManager->getPlayersWorkers(player).at(0), "Worker not found");
}

void Objectmanagertest::testGetPlayersWorkers()
{
    std::shared_ptr<Team::GameEventHandler> t_gameEventHandler(new Team::GameEventHandler);
    std::shared_ptr<Team::ObjectManager> t_objectManager(new Team::ObjectManager);
    std::shared_ptr<Team::PlayerObject> player(new Team::PlayerObject("Test"));

    std::vector<std::shared_ptr<Team::Farmer>> testVector = {};

    // Create 20 workers, and save them to objmgr and testVector
    for (int i = 0; i < 20; i++)
    {
        std::shared_ptr<Team::Farmer> worker(
                    new Team::Farmer(t_gameEventHandler, t_objectManager, player));

        worker->setOwner(player);
        t_objectManager->addWorker(worker);
        testVector.push_back(worker);
    }

    std::vector<std::shared_ptr<Course::WorkerBase>> vectorFromObjMgr =
            t_objectManager->getPlayersWorkers(player);

    // Test that vectors match
    int vectorSize = testVector.size();
    for(int i = 0; i < vectorSize; i++)
    {
        QVERIFY2(testVector.at(i) == vectorFromObjMgr.at(i), "Workers do not match");
    }
}


QTEST_APPLESS_MAIN(Objectmanagertest)

#include "tst_objectmanagertest.moc"
