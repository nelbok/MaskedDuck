#include <QApplication>

#include "editor/mainwindow.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  editor::MainWindow w;
  w.show();
  
  return a.exec();
}
