#include "main_window.h"
#include <QApplication>
#include "factory.h"
#include <memory>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MainWindow win;

  shared_ptr<Factory> factory(new Factory);
  factory->SetMainWindow(&win);
  if (!factory->Init()) {
    qDebug() << "Factory initialization failed";
  }

  win.SetFactory(factory);
  win.show();

  return app.exec();
}
