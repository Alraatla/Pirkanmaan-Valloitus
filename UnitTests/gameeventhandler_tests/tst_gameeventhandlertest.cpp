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

QTEST_APPLESS_MAIN(Gameeventhandlertest)

#include "tst_gameeventhandlertest.moc"
