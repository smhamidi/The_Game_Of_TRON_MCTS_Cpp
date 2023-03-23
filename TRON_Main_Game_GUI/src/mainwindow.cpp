#include "mainwindow.h"
#include "./ui_mainwindow.h"

Config extern_config;
WorldModel extern_wm;
GameState extern_gamestate = GameState::Pause;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocus(); // no defualt focus on any widget

    config_handler = new ConfigHandler{ui};
    game = new Game{};

    game_graphic = new GameGraphic{};
    layout_game_graphic = new QGridLayout{ui->widget_game};
    ui->widget_game->setContentsMargins(0, 0, 0, 0);
    layout_game_graphic->setSpacing(0);
    layout_game_graphic->setContentsMargins(0, 0, 0, 0);
    layout_game_graphic->addWidget(game_graphic);

    broadcast = new BroadCast{};
    broadcast->udp->moveToThread(broadcast);

    receive_command = new ReceiveCommand{};
    connect(ui->lineEdit_command_ip, &QLineEdit::editingFinished, receive_command, &ReceiveCommand::connect_to_hosts);
    connect(ui->lineEdit_blueteam_port, &QLineEdit::editingFinished, receive_command, &ReceiveCommand::connect_to_hosts);
    connect(ui->lineEdit_redteam_port, &QLineEdit::editingFinished, receive_command, &ReceiveCommand::connect_to_hosts);

    // pushbuttons
    connect(ui->pushButton_start_stop, &QPushButton::clicked, this, &MainWindow::handle_start_stop_button);
    connect(ui->pushButton_resetround, &QPushButton::clicked, this, &MainWindow::handle_reset_round_button);
    connect(ui->pushButton_resetgame, &QPushButton::clicked, this, &MainWindow::handle_reset_game_button);

    timer_simulator = new QTimer{};
    connect(timer_simulator, &QTimer::timeout, this, &MainWindow::handle_timer_simulator);
    timer_time = 100;
    timer_simulator->start(timer_time);
    
}

MainWindow::~MainWindow()
{
    delete ui;
    delete config_handler;
    delete game;
    delete game_graphic;
    delete layout_game_graphic;
    delete timer_simulator;
    delete broadcast;
    delete receive_command;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    int min = std::min(ui->widget_game->size().width(), ui->widget_game->size().height());
    game_graphic->setMaximumSize(min, min);
}

void MainWindow::showEvent(QShowEvent* event)
{
    // correcting gameview initial size
    int min = std::min(ui->widget_game->size().width(), ui->widget_game->size().height());
    game_graphic->setMaximumSize(min, min);
}

void MainWindow::update_whole_gui()
{
    game_graphic->repaint();

    ui->label_blueteam_score->setText(QString::number(extern_wm.blue.score));
    ui->label_redteam_score->setText(QString::number(extern_wm.red.score));

    ui->label_blueteam_dir->setText(dir_to_text(extern_wm.blue.dir));
    ui->label_redteam_dir->setText(dir_to_text(extern_wm.red.dir));

    ui->label_blueteam_freq->setText(QString::number(receive_command->blue_command_freq) + " Hz");
    ui->label_redteam_freq->setText(QString::number(receive_command->red_command_freq) + " Hz");
}

void MainWindow::handle_start_stop_button()
{
    this->setFocus();
    if(ui->pushButton_start_stop->text().toUpper() == "START")
    {
        ui->pushButton_start_stop->setText("Pause");
        extern_gamestate = GameState::Running;
    }
    else
    {
        ui->pushButton_start_stop->setText("Start");
        extern_gamestate = GameState::Pause;
    }
}

void MainWindow::handle_reset_round_button()
{
    ui->pushButton_start_stop->setText("Start");
    extern_gamestate = GameState::Pause;
    game->reset_round();
    update_whole_gui();
}

void MainWindow::handle_reset_game_button()
{
    ui->pushButton_start_stop->setText("Start");
    extern_gamestate = GameState::Pause;
    game->reset_game();
    update_whole_gui();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(extern_config.blueteam_handy)
    {
        if(event->key() == Qt::Key_Up)
            extern_wm.blue.dir = Direction::Up;
        else if(event->key() == Qt::Key_Right)
            extern_wm.blue.dir = Direction::Right;
        else if(event->key() == Qt::Key_Down)
            extern_wm.blue.dir = Direction::Down;
        else if(event->key() == Qt::Key_Left)
            extern_wm.blue.dir = Direction::Left;
    }

    if(extern_config.redteam_handy)
    {
        if(event->key() == Qt::Key_W)
            extern_wm.red.dir = Direction::Up;
        else if(event->key() == Qt::Key_D)
            extern_wm.red.dir = Direction::Right;
        else if(event->key() == Qt::Key_S)
            extern_wm.red.dir = Direction::Down;
        else if(event->key() == Qt::Key_A)
            extern_wm.red.dir = Direction::Left;
    }
}

void MainWindow::handle_timer_simulator()
{
    broadcast->start();
    if(extern_gamestate == GameState::Pause) return;
    timer_simulator->stop();

    bool is_finished = game->step();
    update_whole_gui();
    if(is_finished)
    {
        QThread::msleep(500);
        game->reset_round();
        update_whole_gui();
    }
    timer_simulator->start(timer_time);
}