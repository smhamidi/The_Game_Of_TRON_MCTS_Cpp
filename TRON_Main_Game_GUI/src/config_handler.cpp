#include "config_handler.h"

ConfigHandler::ConfigHandler(Ui::MainWindow*& ui, QObject *parent) : QObject{parent}, ui{ui}
{
    connect(ui->lineEdit_field_cellnum, &QLineEdit::editingFinished, this, &ConfigHandler::handle_field_cellnum);
    connect(ui->lineEdit_field_cellwidth, &QLineEdit::editingFinished, this, &ConfigHandler::handle_field_cellwidth);
    connect(ui->lineEdit_broadcast_ip, &QLineEdit::editingFinished, this, &ConfigHandler::handle_broadcast_ip);
    connect(ui->lineEdit_broadcast_port, &QLineEdit::editingFinished, this, &ConfigHandler::handle_broadcast_port);
    connect(ui->lineEdit_command_ip, &QLineEdit::editingFinished, this, &ConfigHandler::handle_command_ip);
    connect(ui->lineEdit_blueteam_name, &QLineEdit::editingFinished, this, &ConfigHandler::handle_blueteam_name);
    connect(ui->lineEdit_blueteam_port, &QLineEdit::editingFinished, this, &ConfigHandler::handle_blueteam_port);
    connect(ui->checkBox_blueteam_handy, &QCheckBox::stateChanged, this, &ConfigHandler::handle_blueteam_handy);
    connect(ui->lineEdit_redteam_name, &QLineEdit::editingFinished, this, &ConfigHandler::handle_redteam_name);
    connect(ui->lineEdit_redteam_port, &QLineEdit::editingFinished, this, &ConfigHandler::handle_redteam_port);
    connect(ui->checkBox_redteam_handy, &QCheckBox::stateChanged, this, &ConfigHandler::handle_redteam_handy);


    ui->lineEdit_field_cellnum->setText("43");
    ui->lineEdit_field_cellwidth->setText("15.0");
    ui->lineEdit_broadcast_ip->setText("255.255.255.255");
    ui->lineEdit_broadcast_port->setText("1234");

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses())
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            ui->lineEdit_command_ip->setText(address.toString());
    
    ui->lineEdit_blueteam_name->setText("BLUE");
    ui->lineEdit_blueteam_port->setText("1235");
    ui->checkBox_blueteam_handy->setChecked(false);
    ui->lineEdit_redteam_name->setText("RED");
    ui->lineEdit_redteam_port->setText("1236");
    ui->checkBox_redteam_handy->setChecked(false);

    emit ui->lineEdit_field_cellnum->editingFinished();
    emit ui->lineEdit_field_cellwidth->editingFinished();
    emit ui->lineEdit_broadcast_ip->editingFinished();
    emit ui->lineEdit_broadcast_port->editingFinished();
    emit ui->lineEdit_command_ip->editingFinished();
    emit ui->lineEdit_blueteam_name->editingFinished();
    emit ui->lineEdit_blueteam_port->editingFinished();
    emit ui->checkBox_blueteam_handy->stateChanged(ui->checkBox_blueteam_handy->isChecked());
    emit ui->lineEdit_redteam_name->editingFinished();
    emit ui->lineEdit_redteam_port->editingFinished();
    emit ui->checkBox_redteam_handy->stateChanged(ui->checkBox_redteam_handy->isChecked());

}

ConfigHandler::~ConfigHandler()
{

}

void ConfigHandler::handle_field_cellnum()
{
    bool ok;
    int dec = ui->lineEdit_field_cellnum->text().toInt(&ok, 10);
    if(!ok) qWarning() << "[field_cellnum] enter a correct number!";
    else if(dec < 6 || dec > 100) qWarning() << "[field_cellnum] number of cells must be between 6 - 100!";
    else extern_config.field_cellnum = dec;
    
}
void ConfigHandler::handle_field_cellwidth()
{
    bool ok;
    int dec = ui->lineEdit_field_cellwidth->text().toFloat(&ok);
    if(!ok) qWarning() << "[field_cellwidth] enter a correct number!";
    // else if(dec < 6 || dec > 50) qWarning() << "[field_cellnum] number of cells must be between 6 - 50!";
    else extern_config.field_cellwidth = dec;
}

void ConfigHandler::handle_broadcast_ip()
{
    QString ip = ui->lineEdit_broadcast_ip->text();
    bool ok = is_valid_ip(ip);
    if(!ok) qWarning() << "[broadcast_ip] enter a correct ip address!";
    else extern_config.broadcast_ip = ip;

}
void ConfigHandler::handle_broadcast_port()
{
    bool ok;
    int dec = ui->lineEdit_broadcast_port->text().toInt(&ok, 10);
    if(!ok) qWarning() << "[broadcast_port] enter a correct number!";
    // else if(dec < 6 || dec > 100) qWarning() << "[field_cellnum] number of cells must be between 6 - 100!";
    else extern_config.broadcast_port = dec;
}

void ConfigHandler::handle_command_ip()
{
    QString ip = ui->lineEdit_command_ip->text();
    bool ok = is_valid_ip(ip);
    if(!ok) qWarning() << "[command_ip] enter a correct ip address!";
    else extern_config.command_ip = ip;
}

void ConfigHandler::handle_blueteam_name()
{
    QString name = ui->lineEdit_blueteam_name->text();
    if(name.length() > 15) qWarning() << "[blueteam_name] name cant have more thant 15 characters!";
    else
    {
        extern_config.blueteam_name = name;
        ui->label_blueteam_name->setText(name);
    }
}
void ConfigHandler::handle_blueteam_port()
{
    bool ok;
    int dec = ui->lineEdit_blueteam_port->text().toInt(&ok, 10);
    if(!ok) qWarning() << "[blueteam_port] enter a correct number!";
    // else if(dec < 6 || dec > 100) qWarning() << "[field_cellnum] number of cells must be between 6 - 100!";
    else extern_config.blueteam_port = dec;
}
void ConfigHandler::handle_blueteam_handy()
{
    extern_config.blueteam_handy = ui->checkBox_blueteam_handy->isChecked();
}

void ConfigHandler::handle_redteam_name()
{
    QString name = ui->lineEdit_redteam_name->text();
    if(name.length() > 15) qWarning() << "[redteam_name] name cant have more thant 15 characters!";
    else
    {
        extern_config.redteam_name = name;
        ui->label_redteam_name->setText(name);
    }
}
void ConfigHandler::handle_redteam_port()
{
    bool ok;
    int dec = ui->lineEdit_redteam_port->text().toInt(&ok, 10);
    if(!ok) qWarning() << "[redteam_port] enter a correct number!";
    // else if(dec < 6 || dec > 100) qWarning() << "[field_cellnum] number of cells must be between 6 - 100!";
    else extern_config.redteam_port = dec;
}
void ConfigHandler::handle_redteam_handy()
{
    extern_config.redteam_handy = ui->checkBox_redteam_handy->isChecked();
}

bool ConfigHandler::valid_part(char* s)
{
    int n = strlen(s);

    if (n > 3)
        return false;

    for (int i = 0; i < n; i++)
        if ((s[i] >= '0' && s[i] <= '9') == false)
            return false;
    std::string str(s);

    if (str.find('0') == 0 && n > 1)
        return false;
    std::stringstream geek(str);
    int x;
    geek >> x;
     
    return (x >= 0 && x <= 255);
}

bool ConfigHandler::is_valid_ip(const QString& ip)
{
    char* ip_str = ip.toLocal8Bit().data();
    if (ip_str == NULL)
        return false;
    int i, num, dots = 0;
    int len = strlen(ip_str);
    int count = 0;
     
    for (int i = 0; i < len; i++)
        if (ip_str[i] == '.')
            count++;
    if (count != 3)
        return false;
     
   
    char *ptr = strtok(ip_str, ".");
    if (ptr == NULL)
        return false;
 
    while (ptr) {
 
        if (valid_part(ptr))
        {
            ptr = strtok(NULL, ".");
            if (ptr != NULL)
                ++dots;
        }
        else
            return false;
    }
 
    if (dots != 3)
        return false;
    return true;
}
