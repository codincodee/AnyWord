#include "main_window.h"
#include <QApplication>
#include <memory>
#include <QDebug>
#include "factory.h"

using namespace std;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
//  MainWindow win;
//  if (!win.Init()) {
//    return -1;
//  }
//  win.show();
  Factory factory;

  return app.exec();
}
