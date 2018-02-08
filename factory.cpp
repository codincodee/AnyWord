#include "factory.h"
#include "main_window.h"
#include "database.h"
#include "add_words_main_window.h"

Factory::Factory()
{
}

bool Factory::Construct() {
  auto main_window = new MainWindow;
  main_window->Init();
  main_window->show();
  recycle_widgets_.push_back(main_window);

  auto add_words_main_window = new AddWordsMainWindow;
  recycle_widgets_.push_back(add_words_main_window);

  auto database = new Database;
  recycle_objects_.push_back(database);

  connect(
      main_window,
      SIGNAL(ShowAddWordsMainWindow()),
      add_words_main_window,
      SLOT(show()));

  connect(
      add_words_main_window,
      SIGNAL(WriteDatabase(std::shared_ptr<int>)),
      database,
      SLOT(OnWriteDatabase(std::shared_ptr<int>)));
  return true;
}

Factory::~Factory() {
  for (auto& obj : recycle_objects_) {
    delete obj;
  }
}
