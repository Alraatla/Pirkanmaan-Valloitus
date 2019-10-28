#include "gamemenu.h"
#include "ui_gamemenu.h"

Gamemenu::Gamemenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gamemenu)
{
    ui->setupUi(this);
}

Gamemenu::~Gamemenu()
{
    delete ui;
}
