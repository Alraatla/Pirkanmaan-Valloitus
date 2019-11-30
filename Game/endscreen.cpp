#include "endscreen.h"
#include "mapwindow.hh"
#include "ui_endscreen.h"

EndScreen::EndScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndScreen)
{
    ui->setupUi(this);

    connect(parent,
            SIGNAL(playerObject(std::shared_ptr<Team::PlayerObject>, int)),
            this,
            SLOT(endScreenSetup(std::shared_ptr<Team::PlayerObject>, int)));
    connect(ui->closeButton, &QPushButton::clicked, this, &EndScreen::pressClose);


}

EndScreen::~EndScreen()
{
    delete ui;
}

void EndScreen::pressClose()
{
    this->close();
}

void EndScreen::endScreenSetup(std::shared_ptr<Team::PlayerObject> player,
                               int rounds)
{

    ui->playerNameLabel->setText(QString::fromStdString(player->getName()));
    ui->pointsAmountLabel->setText(QString::number(player->getPoints()));
    ui->roundsAmountLabel->setText(QString::number(rounds));

}
