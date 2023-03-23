#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QObject>
#include <QDebug>
#include "extern.h"

class Game : public QObject
{
    Q_OBJECT

public:
    Game(QObject* parent = nullptr);
    ~Game();

    void reset_board();
    void reset_round();
    void reset_game();

    bool step();

    static void print_board();

private:
    // shortcuts to extern variables
    Board& board;
    int& cell_num;
    Tron& blue;
    Tron& red;

};

#endif // GAME_H