#include <QApplication>
#include <QDebug>

#include "Game.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
  std::cout << "main.cpp" << std::endl;

  QApplication a(argc, argv);

  MainWindow w;
  w.show();
  return a.exec();
}
//************************//

// // Node Class test
// Node mynode{};
// int depth = 9;
// for (size_t i = 0; i < depth; i++) {
//   mynode.expansion();
// }
// std::cout << mynode.getAllNodes().size() << std::endl;
// std::cout << mynode.get_childs()[1]->getAllNodes().size() << std::endl;

// for (auto i : mynode.get_childs()[1]->getAllNodes()) {
//   if (i == mynode.get_childs()[1]->get_childs()[2]) {
//     std::cout << "my condulence" << std::endl;
//   }
// }

// std::cout << mynode.get_childs()[1]->get_childs()[2]->calcValue()
//           << std::endl;

//************************//

// // Map Class test
// Map ourMap{10, 10, 3, 3, 7, 7};
// ourMap.dispMap();
// ourMap.updateMap(1, 1);
// ourMap.updateMap(2, 2);
// ourMap.dispMap();

//************************//

// return 0;
// }