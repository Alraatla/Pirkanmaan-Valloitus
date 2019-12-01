#include <QString>
#include <QtTest>
#include <algorithm>
#include <utility>

#include "objectmanager.h"
#include "gameeventhandler.h"

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
    int vectorSize = t_objectManager->getTilesForMap().size();
//    int vectorSize = static_cast<int>(vectorSize);
    QVERIFY2(size == vectorSize, "Error, vector not right size");

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
//    qDebug() << testTile->ID << " Should be " << data.tile->ID;

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

    const char* currentData = QTest::currentDataTag();
    const char* dataName = "Empty vector";

    if(currentData == dataName)
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

}

void Objectmanagertest::testGetTilesForMap()
{

}


QTEST_APPLESS_MAIN(Objectmanagertest)

#include "tst_objectmanagertest.moc"
