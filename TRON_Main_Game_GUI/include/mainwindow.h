#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include "extern.h"
#include "config_handler.h"
#include "game.h"
#include "game_graphic.h"
#include "network.h"

// forward declaration
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ConfigHandler* config_handler;
    Game* game;

    GameGraphic* game_graphic;
    QGridLayout* layout_game_graphic;

    QTimer* timer_simulator;
    int timer_time;

    BroadCast* broadcast;
    ReceiveCommand* receive_command;

    void update_whole_gui();

private slots:
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void handle_start_stop_button();
    void handle_reset_round_button();
    void handle_reset_game_button();

    void handle_timer_simulator();

};


#endif // MAINWINDOW_H