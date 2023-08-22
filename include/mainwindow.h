#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Game.h"
#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void handleUdp();
    void settingChanged();
    void clicked();


private:
    QUdpSocket udp;
    Ui::MainWindow* ui;
    bool firstRun;
    bool isCom;
    Game* ourGame;

    // QSignalBlocker blocker;
};
#endif // MAINWINDOW_H
