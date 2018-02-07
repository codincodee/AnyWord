#include "main_window.h"
#include <QApplication>
#include "factory.h"
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MainWindow win;

  shared_ptr<Factory> factory(new Factory);
  factory->SetMainWindow(&win);
  factory->Init();

  win.SetFactory(factory);
  win.show();

  return app.exec();
}
