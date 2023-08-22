#include "game_graphic.h"



GameGraphic::GameGraphic(QOpenGLWidget* parent) : QOpenGLWidget{parent},
    board{extern_wm.board}, cell_num{extern_config.field_cellnum}, cell_width{extern_config.field_cellwidth}, blue{extern_wm.blue}, red{extern_wm.red}, scale_ratio{1}
{
    painter = new QPainter{};
}

GameGraphic::~GameGraphic()
{
    delete painter;
}

void GameGraphic::paintGL()
{
    painter->begin(this);

//    auto pal = this->palette();
//    pal.setColor(QPalette::ColorRole::Base, Qt::white);
//    this->setAutoFillBackground(true);
//    this->setPalette(pal);

    painter->translate(width() / 2, height() / 2); // bring the reference coordinate to the middle
    painter->scale(scale_ratio, -scale_ratio);

    // empthy board
    painter->setPen(QPen(Qt::black, 1.5));
    for(float i{}; i <= board.size(); i++)
    {
        painter->drawLine(CVT(i, 0), CVT(i, cell_num));
        painter->drawLine(CVT(0, i), CVT(cell_num, i));
    }

    for(int i{}; i < board.size(); i++)
        for(int j{}; j < board.size(); j++)
        {
            // borders
            painter->setPen(Qt::NoPen);
            painter->setBrush(Qt::black);
            if(board[i][j] == -1)
                painter->drawRect({CVT(i, j), QSizeF(cell_width, -cell_width)});
            // blue tron
            painter->setPen(QPen(Qt::black, 1));
            painter->setBrush(Qt::blue);
            if(board[i][j] == 1)
                painter->drawRect({CVT(i, j), QSizeF(cell_width, -cell_width)});   
            // red tron
            painter->setPen(QPen(Qt::black, 1));
            painter->setBrush(Qt::red);
            if(board[i][j] == 2) 
                painter->drawRect({CVT(i, j), QSizeF(cell_width, -cell_width)});
        }

        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::darkBlue);
        painter->drawRect({CVT(blue.head.top().x(), blue.head.top().y()), QSizeF(cell_width, -cell_width)});
        painter->setBrush(Qt::darkRed);
        painter->drawRect({CVT(red.head.top().x(), red.head.top().y()), QSizeF(cell_width, -cell_width)});

    painter->end();
}

void GameGraphic::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameGraphic::wheelEvent(QWheelEvent * event)
{
    int delta = event->angleDelta().x() + event->angleDelta().y();
    if (delta < 0)
        scale_ratio +=0.01;
    else if (delta > 0)
        scale_ratio -=0.01;

    if (scale_ratio <= 0)
        scale_ratio = 0.01;
    update();
}
