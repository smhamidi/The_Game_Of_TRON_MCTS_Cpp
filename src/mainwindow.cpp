#include "mainwindow.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkDatagram>
#include <chrono>

#include "../ui_mainwindow.h"

QString opponentTeamColor{};
QString ourTeamColor{};
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      isCom{false},
      ourGame{nullptr} {
  udp.blockSignals(true);
  ui->setupUi(this);
  // udp.bind(QHostAddress { ui->lineEdit_2->text() },
  // ui->lineEdit_4->text().toInt()); connect(&udp, &QUdpSocket::readyRead,
  // this, &MainWindow::handleUdp); ui->comboBox->addItem("1");
  // ui->comboBox->addItem("2");
  // ui->comboBox->addItem("3");
  // ui->comboBox->addItem("4");
  // ui->comboBox->addItem("5");

  connect(&udp, &QUdpSocket::readyRead, this, &MainWindow::handleUdp);
  connect(ui->lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::settingChanged);
  connect(ui->lineEdit_2, &QLineEdit::editingFinished, this,
          &MainWindow::settingChanged);
  connect(ui->lineEdit_3, &QLineEdit::editingFinished, this,
          &MainWindow::settingChanged);
  connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::clicked);
}

void MainWindow::clicked() {
  udp.blockSignals(false);
  // qDebug() << ui->lineEdit_2->text() << "1234";
  udp.bind(1234);
  // connect(&udp, &QUdpSocket::readyRead, this, &MainWindow::handleUdp);
}

void MainWindow::settingChanged() {
  udp.blockSignals(true);
  qDebug() << "setting changed!";
}

void MainWindow::handleUdp() {
  qDebug() << "data receive!";
  QNetworkDatagram massage{udp.receiveDatagram()};
  if (false) {
    qDebug() << "damped!";
  } else if (isCom) {
    QJsonDocument massageJson{QJsonDocument::fromJson(massage.data())};

    QJsonValue head1{massageJson[ourTeamColor].toArray()[0]};

    QJsonValue head2{massageJson[opponentTeamColor].toArray()[0]};

    if (massageJson["game_state"].toString().toLower() == "running") {
      if (!(ourGame->updateGame(static_cast<size_t>(head1[1].toInt()),
                                static_cast<size_t>(head1[0].toInt()),
                                static_cast<size_t>(head2[1].toInt()),
                                static_cast<size_t>(head2[0].toInt())))) {
        isCom = false;
      }
    }

    auto t{std::chrono::system_clock::now()};
    ourGame->monteCarlo(t);
    int ourCMD{selectionToMove(ourGame->get_node1())->get_globalDir()};
    // qDebug() << ourCMD;
    // qDebug() << selection(ourGame->get_node1())->get_wCnt();
    // qDebug() << "childs value with " <<
    // ourGame->get_node1()->get_childs()[0]->get_globalDir() <<
    // ourGame->get_node1()->get_childs()[0]->calcValue(); qDebug() << "childs
    // value with " << ourGame->get_node1()->get_childs()[1]->get_globalDir() <<
    // ourGame->get_node1()->get_childs()[1]->calcValue(); qDebug() << "childs
    // value with " << ourGame->get_node1()->get_childs()[2]->get_globalDir() <<
    // ourGame->get_node1()->get_childs()[2]->calcValue();

    if (ourCMD == 0) {
      QString temp{"down"};
      udp.writeDatagram(temp.toStdString().c_str(), temp.length(),
                        QHostAddress{ui->lineEdit_2->text()},
                        ui->lineEdit_4->text().toInt());
    } else if (ourCMD == 1) {
      QString temp{"left"};
      udp.writeDatagram(temp.toStdString().c_str(), temp.length(),
                        QHostAddress{ui->lineEdit_2->text()},
                        ui->lineEdit_4->text().toInt());
    } else if (ourCMD == 2) {
      QString temp{"up"};
      udp.writeDatagram(temp.toStdString().c_str(), temp.length(),
                        QHostAddress{ui->lineEdit_2->text()},
                        ui->lineEdit_4->text().toInt());

    } else if (ourCMD == 3) {
      QString temp{"right"};
      udp.writeDatagram(temp.toStdString().c_str(), temp.length(),
                        QHostAddress{ui->lineEdit_2->text()},
                        ui->lineEdit_4->text().toInt());
    }
    // qDebug() << ;
  } else {
    isCom = true;
    // QNetworkDatagram massage { udp.receiveDatagram() };
    // qDebug() << massage.data();

    QJsonDocument massageJson{QJsonDocument::fromJson(massage.data())};
    QString ourTeamName{ui->lineEdit->text()};
    ourTeamColor = (massageJson["blue"].toString() == ourTeamName)
                       ? "blue_heads"
                       : "red_heads";
    opponentTeamColor = (massageJson["red"].toString() == ourTeamName)
                            ? "blue_heads"
                            : "red_heads";
    if (ui->lineEdit_3->text().toInt() != massageJson["game_dim"].toInt()) {
      return;
    }
    size_t dim{static_cast<size_t>(ui->lineEdit_3->text().toInt())};
    QJsonValue head1{massageJson[ourTeamColor].toArray()[0]};
    QJsonValue head2{massageJson[opponentTeamColor].toArray()[0]};
    // qDebug() << head2;
    // qDebug() << head1;

    // qDebug() << "fuck you!";

    ourGame =
        new Game{static_cast<size_t>(dim),
                 static_cast<size_t>(dim),
                 static_cast<size_t>(head1[1].toInt()),
                 static_cast<size_t>(head1[0].toInt()),
                 static_cast<size_t>(head2[1].toInt()),
                 static_cast<size_t>(head2[0].toInt()),
                 static_cast<size_t>(ui->comboBox->currentText().toInt())};
  }
}

MainWindow::~MainWindow() {
  delete ui;
  delete ourGame;
}
