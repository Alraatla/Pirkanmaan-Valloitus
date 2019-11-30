#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QDialog>
#include "playerobject.h"

namespace Ui {
class EndScreen;
}

class EndScreen : public QDialog
{
    Q_OBJECT

public:
    explicit EndScreen(QWidget *parent = 0);
    ~EndScreen();

public slots:
    void endScreenSetup(std::shared_ptr<Team::PlayerObject> player,
                        int rounds);

private slots:
    void pressClose();

private:
    Ui::EndScreen *ui;
};

#endif // ENDSCREEN_H
