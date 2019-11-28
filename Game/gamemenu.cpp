#include "gamemenu.h"
#include "ui_gamemenu.h"

Gamemenu::Gamemenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gamemenu)
{
    ui->setupUi(this);
    connect(ui->okAndCancelButtons, &QDialogButtonBox::accepted, this, &Gamemenu::pressOk);
    connect(ui->playerCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(playerCountChanged(int)));


}

Gamemenu::~Gamemenu()
{
    delete ui;
}

void Gamemenu::pressOk()
{
    std::vector<std::string> playerNames = {};

    playerNames.push_back(ui->player1NameEdit->displayText().toStdString());
    playerNames.push_back(ui->player2NameEdit->displayText().toStdString());

    if(ui->player3NameEdit->isEnabled())
    {
        playerNames.push_back(ui->player3NameEdit->displayText().toStdString());
        if(ui->player4NameEdit->isEnabled())
        {
            playerNames.push_back(ui->player4NameEdit->displayText().toStdString());
        }
    }
    if(ui->pointsRadioButton->isChecked())
    {
        emit initializeGame(ui->playerCountSpinBox->value(), playerNames, true, ui->pointsSpinBox->value());
    }
    else
    {
        emit initializeGame(ui->playerCountSpinBox->value(), playerNames, false, ui->roundsSpinBox->value());
    }

}

void Gamemenu::pressCancel()
{

}

void Gamemenu::playerCountChanged(int playerAmount)
{
    if(playerAmount == 2)
    {
        ui->player3NameEdit->setDisabled(true);
        ui->player4NameEdit->setDisabled(true);
    }
    else if (playerAmount == 3) {
        ui->player3NameEdit->setDisabled(false);
        ui->player4NameEdit->setDisabled(true);
    }
    else
    {
        ui->player3NameEdit->setDisabled(false);
        ui->player4NameEdit->setDisabled(false);
    }
}
