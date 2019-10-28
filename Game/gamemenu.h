#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>

namespace Ui {
class Gamemenu;
}

class Gamemenu : public QDialog
{
    Q_OBJECT

public:
    explicit Gamemenu(QWidget *parent = 0);
    ~Gamemenu();

private:
    Ui::Gamemenu *ui;
};

#endif // GAMEMENU_H
