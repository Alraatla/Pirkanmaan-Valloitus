#include <QString>
#include <QtTest>
#include <algorithm>

#include "objectmanager.h"
#include "gameeventhandler.h"

struct testTileData
{
    Course::Coordinate coordinate = {0 , 0};
    int x;
    int y;
    Course::ObjectId id;
    std::shared_ptr<Course::TileBase> tile;
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

//    void testGetTile_data();
//    void testGetTile();
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

//void Objectmanagertest::testGetTile_data()
//{
//    QTest::addColumn<int>("width");
//    QTest::addColumn<int>("height");
//    QTest::addColumn<int>("xCoordinate");
//    QTest::addColumn<int>("yCoordinate");

//    QTest::newRow("Small map, tile in corner") << 5 << 3 << 5*3;
//    QTest::newRow("One tile") << 1 << 1 << 0 << 0;
//    QTest::newRow("Big map") << 50 << 30 << 10 << 29;
//}

//void Objectmanagertest::testGetTile()
//{
//    QFETCH(int, width);
//    QFETCH(int, height);
//    QFETCH(int, xCoordinate);
//    QFETCH(int, yCoordinate);

//    std::shared_ptr<Team::ObjectManager> t_objectManager(new Team::ObjectManager);
//    testTileData data = {};
//    data.x = xCoordinate;
//    data.y = yCoordinate;

//    std::vector<std::shared_ptr<Course::TileBase>> tiles =
//            makeTiles(width, height, t_objectManager, data);

//    Course::Coordinate testCoordinate(xCoordinate, yCoordinate);

//    t_objectManager->getTile()


//}

QTEST_APPLESS_MAIN(Objectmanagertest)

#include "tst_objectmanagertest.moc"
