#include <QApplication>

#include "game/mainwindow.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  game::MainWindow w;
  w.show();

  return a.exec();
}
