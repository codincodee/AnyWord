#include "main_window.h"
#include <QApplication>
#include <memory>
#include <QDebug>
#include "factory.h"

using namespace std;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Factory factory;
  factory.Construct();
  return app.exec();
}
