#include "gamemenu.h"
#include "ui_gamemenu.h"

Gamemenu::Gamemenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gamemenu)
{
    ui->setupUi(this);
    connect(ui->okAndCancelButtons, SIGNAL(accepted()), this, SLOT(pressOk()));
}

Gamemenu::~Gamemenu()
{
    delete ui;
}

void Gamemenu::pressOk()
{
    emit initializeGame(ui->playerCountSpinBox->value());
}
