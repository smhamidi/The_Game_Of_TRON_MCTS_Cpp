#include "network.h"


BroadCast::BroadCast(QThread* parent) : QThread{parent},
    ip{extern_config.broadcast_ip}, port{extern_config.broadcast_port}, board{extern_wm.board}, blue{extern_wm.blue}, red{extern_wm.red}
{
    udp = new QUdpSocket{};
}

BroadCast::~BroadCast()
{
    delete udp;
}

void BroadCast::run()
{
    QJsonObject main_json;
    // game state
    main_json.insert("game_dim", QJsonValue::fromVariant(extern_config.field_cellnum));
    main_json.insert("game_state", QJsonValue::fromVariant(state_to_text(extern_gamestate)));

    // team names
    main_json.insert("blue", QJsonValue::fromVariant(extern_config.blueteam_name));
    main_json.insert("red", QJsonValue::fromVariant(extern_config.redteam_name));

    // team scores
    main_json.insert("blue_score", QJsonValue::fromVariant(blue.score));
    main_json.insert("red_score", QJsonValue::fromVariant(red.score));

    // team heads - blue
    QJsonArray blue_heads;
    auto tmp = blue.head;
    while(!tmp.empty())
    {
        QJsonArray head;
        head.push_back(tmp.top().x());
        head.push_back(tmp.top().y());
        blue_heads.push_back(head);
        tmp.pop();
    }
    main_json.insert("blue_heads", blue_heads);

    // team heads - red
    QJsonArray red_heads;
    tmp = red.head;
    while(!tmp.empty())
    {
        QJsonArray head;
        head.push_back(tmp.top().x());
        head.push_back(tmp.top().y());
        red_heads.push_back(head);
        tmp.pop();
    }
    main_json.insert("red_heads", red_heads);

    QJsonDocument doc(main_json);
    QByteArray dgram = doc.toJson(QJsonDocument::Compact);
    
    // std::cout << dgram.toStdString() << std::endl;
    auto ret = udp->writeDatagram(dgram.data(), dgram.size(), QHostAddress{ip}, 1234);
    // qDebug() << ret << dgram.size();
}





ReceiveCommand::ReceiveCommand(QObject* parent) : QObject{parent},
    ip{extern_config.command_ip}, blue_port{extern_config.blueteam_port}, red_port{extern_config.redteam_port}, blue{extern_wm.blue}, red{extern_wm.red}
{

    blue_receive_counter = 0;
    red_receive_counter = 0;
    blue_command_freq = 0;
    red_command_freq = 0;

    timer = new QTimer{};
    connect(timer, &QTimer::timeout, this, &ReceiveCommand::handle_timer);
    timer->start(1000);

    blue_udp = new QUdpSocket{};
    connect(blue_udp, &QUdpSocket::readyRead, this, &ReceiveCommand::handle_blue_command);

    red_udp = new QUdpSocket{};
    connect(red_udp, &QUdpSocket::readyRead, this, &ReceiveCommand::handle_red_command);


    connect_to_hosts();
}

ReceiveCommand::~ReceiveCommand()
{
    delete blue_udp;
    delete red_udp;
}

void ReceiveCommand::connect_to_hosts()
{
    blue_udp->disconnectFromHost();
    blue_udp->bind(QHostAddress(ip), blue_port);

    red_udp->disconnectFromHost();
    red_udp->bind(QHostAddress(ip), red_port);
}

void ReceiveCommand::handle_blue_command()
{
    blue_receive_counter++;
    QNetworkDatagram datagram = blue_udp->receiveDatagram();
    QString recv = QString(datagram.data()).trimmed().toUpper();
    if(!extern_config.blueteam_handy)
    {
        if(recv == "UP")
            blue.dir = Direction::Up;
        else if(recv == "RIGHT")
            blue.dir = Direction::Right;
        else if(recv == "DOWN")
            blue.dir = Direction::Down;
        else // LEFT
            blue.dir = Direction::Left;        
    }
}

void ReceiveCommand::handle_red_command()
{
    red_receive_counter++;
    QNetworkDatagram datagram = red_udp->receiveDatagram();
    QString recv = QString(datagram.data()).trimmed().toUpper();
    if(!extern_config.redteam_handy)
    {
        if(recv == "UP")
            red.dir = Direction::Up;
        else if(recv == "RIGHT")
            red.dir = Direction::Right;
        else if(recv == "DOWN")
            red.dir = Direction::Down;
        else // LEFT
            red.dir = Direction::Left;        
    }

}

void ReceiveCommand::handle_timer()
{
    blue_command_freq = (blue_receive_counter == 0) ? 0 : 1.0/blue_receive_counter;
    red_command_freq = (red_receive_counter == 0) ? 0 : 1.0/red_receive_counter;
    blue_receive_counter = 0;
    red_receive_counter = 0;
}