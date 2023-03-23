#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QObject>
#include <QIntValidator>
#include <QHostAddress>
#include <QNetworkInterface>
#include <string>
#include <sstream>
#include "../src/ui_mainwindow.h"
#include "extern.h"

class ConfigHandler : public QObject
{
    Q_OBJECT
public:
    ConfigHandler(Ui::MainWindow*& ui, QObject *parent = nullptr);
    ~ConfigHandler();

private:
    Ui::MainWindow *ui;

private:
    void handle_field_cellnum();
    void handle_field_cellwidth();

    void handle_broadcast_ip();
    void handle_broadcast_port();

    void handle_command_ip();

    void handle_blueteam_name();
    void handle_blueteam_port();
    void handle_blueteam_handy();

    void handle_redteam_name();
    void handle_redteam_port();
    void handle_redteam_handy();

    // ip validation
    static bool valid_part(char* s);
    static bool is_valid_ip(const QString& ip);


private slots:


};


#endif // CONFIGHANDLER_H