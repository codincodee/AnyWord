#include "factory.h"
#include "main_window.h"
#include "database.h"

Factory::Factory()
{
  auto main_window = new MainWindow;
  main_window->Init();
  main_window->show();

//  data
}

Factory::~Factory() {
  for (auto& obj : objects_) {
    delete obj;
  }
}
