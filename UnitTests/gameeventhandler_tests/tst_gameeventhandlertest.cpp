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
    void testModifyResource();
};

Gameeventhandlertest::Gameeventhandlertest()
{
    QTEST_ASSERT(true == 1);
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
    Course::ResourceMap testResources = {{Course::MONEY, -1260},
                                         {Course::FOOD, -1390},
                                         {Course::WOOD, -755},
                                         {Course::STONE, -500},
                                         {Course::ORE, 0}};
    Course::ResourceMap testShouldBeResources = {{Course::MONEY, 0},
                                                 {Course::FOOD, 0},
                                                 {Course::WOOD, 0},
                                                 {Course::STONE, 0},
                                                 {Course::ORE, 0}};
    gameEventHandler_ptr->modifyResources(std::dynamic_pointer_cast<Course::PlayerBase>(testPlayer),
                                          testResources);
    QTEST_ASSERT(testPlayer->getResources() == testShouldBeResources);
    testResources = {{Course::MONEY, 9999},
                     {Course::FOOD, 9999},
                     {Course::WOOD, 9999},
                     {Course::STONE, 9999},
                     {Course::ORE, 9999}};
    testShouldBeResources = {{Course::MONEY, 9999},
                             {Course::FOOD, 9999},
                             {Course::WOOD, 9999},
                             {Course::STONE, 9999},
                             {Course::ORE, 9999}};

    gameEventHandler_ptr->modifyResources(std::dynamic_pointer_cast<Course::PlayerBase>(testPlayer),
                                          testResources);
    QTEST_ASSERT(testPlayer->getResources() == testShouldBeResources);

    testResources = {{Course::MONEY, -99999},
                     {Course::FOOD, -99999},
                     {Course::WOOD, -99999},
                     {Course::STONE, -99999},
                     {Course::ORE, -99999}};
    QTEST_ASSERT(gameEventHandler_ptr->modifyResources(
                 std::dynamic_pointer_cast<Course::PlayerBase>(testPlayer),
                 testResources) == false);
}

void Gameeventhandlertest::testModifyResource()
{
    std::shared_ptr<Team::GameEventHandler> gameEventHandler_ptr =
            std::make_shared<Team::GameEventHandler>();
    std::shared_ptr<Team::PlayerObject> testPlayer =
            std::make_shared<Team::PlayerObject>("Test");
    gameEventHandler_ptr->modifyResource(testPlayer,
                          Course::BasicResource::MONEY, -1260);
    gameEventHandler_ptr->modifyResource(testPlayer,
                          Course::BasicResource::ORE, 9000);
    QTEST_ASSERT(testPlayer->getResources().at(Course::BasicResource::MONEY) == 0);
    QTEST_ASSERT(testPlayer->getResources().at(Course::BasicResource::ORE) == 9000);
    QTEST_ASSERT(gameEventHandler_ptr->modifyResource(testPlayer,
                 Course::BasicResource::WOOD, -6000) == false);

}

QTEST_APPLESS_MAIN(Gameeventhandlertest)

#include "tst_gameeventhandlertest.moc"
