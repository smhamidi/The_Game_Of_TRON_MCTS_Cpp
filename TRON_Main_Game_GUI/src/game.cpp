#include "game.h"

Game::Game(QObject* parent) : QObject{parent},
    board{extern_wm.board}, cell_num{extern_config.field_cellnum}, blue{extern_wm.blue}, red{extern_wm.red}
{
    reset_game();
}

Game::~Game()
{

}

void Game::reset_board()
{
    board.clear();
    for(int i{}; i < cell_num; i++)
        board.push_back(QVector<int>(cell_num, 0));

    // add borders
    for(int i{}; i < cell_num; i++)
    {
        board[0][i] = -1; board[cell_num-1][i] = -1;
        board[i][0] = -1; board[i][cell_num-1] = -1;
    }

    // initialize blue tron
    blue.tail = QPoint{cell_num/2, cell_num/2 + 2};
    blue.head.clear();
    blue.head.push(blue.tail);
    board[blue.head.top().x()][blue.head.top().y()] = 1;
    blue.dir = Direction::Right; // or static_cast<Direction>(1)

    // initialize red tron
    red.tail = QPoint{cell_num/2, cell_num/2 - 2};
    red.head.clear();
    red.head.push(red.tail);
    board[red.head.top().x()][red.head.top().y()] = 2;
    red.dir = Direction::Left; // or static_cast<Direction>(3)
}

void Game::reset_round()
{
    reset_board();
}

void Game::reset_game()
{
    reset_board();
    blue.score = 0;
    red.score = 0;
}

bool Game::step()
{
    if(blue.dir == Direction::Up)
        blue.head.push(blue.head.top() + QPoint{-1, 0});
    else if(blue.dir == Direction::Right)
        blue.head.push(blue.head.top() + QPoint{0, 1});
    else if(blue.dir == Direction::Down)
        blue.head.push(blue.head.top() + QPoint{1, 0});
    else //Left
        blue.head.push(blue.head.top() + QPoint{0, -1});

    if(red.dir == Direction::Up)
        red.head.push(red.head.top() + QPoint{-1, 0});
    else if(red.dir == Direction::Right)
        red.head.push(red.head.top() + QPoint{0, 1});
    else if(red.dir == Direction::Down)
        red.head.push(red.head.top() + QPoint{1, 0});
    else //Left
        red.head.push(red.head.top() + QPoint{0, -1});

    bool is_finished = false;
    if(blue.head.top() == red.head.top())
    {
        blue.score++; red.score++;
        is_finished = true;
    }
    if(board[blue.head.top().x()][blue.head.top().y()] != 0)
    {
        red.score++;
        is_finished = true;
    }
    if(board[red.head.top().x()][red.head.top().y()] != 0)
    {
        blue.score++;
        is_finished = true;
    }

    board[blue.head.top().x()][blue.head.top().y()] = 1;
    board[red.head.top().x()][red.head.top().y()] = 2;  

    return is_finished;
}

void Game::print_board()
{
    for(const auto& row : extern_wm.board)
    {
        for(const auto& cell : row)
            std::cout << cell << "  ";
        std::cout << std::endl;
    }
}



