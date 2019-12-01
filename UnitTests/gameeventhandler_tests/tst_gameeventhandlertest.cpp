#include <QString>
#include <QtTest>

#include "gameeventhandler.h"

class Gameeventhandlertest : public QObject
{
    Q_OBJECT

public:
    Gameeventhandlertest();

private Q_SLOTS:
    void testMakeNegative();
    void testModifyResources();
};

Gameeventhandlertest::Gameeventhandlertest()
{
}

void Gameeventhandlertest::testMakeNegative()
{
    Team::GameEventHandler* gameEventHandler_ptr = new Team::GameEventHandler;
    Course::ResourceMap testMap = {
        {Course::MONEY, 0},
        {Course::ORE, 200},
        {Course::FOOD, -1},
        {Course::WOOD, 200},
        {Course::STONE, 999999}
    };
    Course::ResourceMap TestShouldBeMap = {
        {Course::MONEY, 0},
        {Course::ORE, -200},
        {Course::FOOD, 1},
        {Course::WOOD, -200},
        {Course::STONE, -999999}
    };
    Course::ResourceMap negativeTestMap =
            gameEventHandler_ptr->makeNegative(testMap);
    delete gameEventHandler_ptr;
    QTEST_ASSERT(negativeTestMap == TestShouldBeMap);
}

void Gameeventhandlertest::testModifyResources()
{
    std::shared_ptr<Team::GameEventHandler> gameEventHandler_ptr =
            std::make_shared<Team::GameEventHandler>();
    std::shared_ptr<Team::PlayerObject> testPlayer =
            std::make_shared<Team::PlayerObject>("Test");
    Course::ResourceMap testResources = {{Course::MONEY, -2500},
                                         {Course::FOOD, -3000},
                                         {Course::WOOD, -2000},
                                         {Course::STONE, -1000},
                                         {Course::ORE, 0}};
    Course::ResourceMap testShouldBeResources = {{Course::MONEY, 0},
                                         {Course::FOOD, 0},
                                         {Course::WOOD, 0},
                                         {Course::STONE, 0},
                                         {Course::ORE, 0}};
    gameEventHandler_ptr->modifyResources(std::dynamic_pointer_cast<Course::PlayerBase>(testPlayer),
                                          testResources);
    QTEST_ASSERT(testPlayer->getResources() == testShouldBeResources);
}

QTEST_APPLESS_MAIN(Gameeventhandlertest)

#include "tst_gameeventhandlertest.moc"
