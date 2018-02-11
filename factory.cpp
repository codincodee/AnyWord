#include "factory.h"
#include "main_window.h"
#include "database.h"
#include "add_words_main_window.h"
#include "select_book_main_window.h"
#include "bookshelf.h"

Factory::Factory()
{
}

bool Factory::Construct() {
  auto main_window = new MainWindow;
  main_window->Init();
  main_window->show();
  recycle_widgets_.push_back(main_window);

  auto add_words_main_window = new AddWordsMainWindow(main_window);
  auto select_book_main_window = new SelectBookMainWindow(main_window);

  auto bookshelf = new Bookshelf;
  recycle_objects_.push_back(bookshelf);

  connect(
      main_window,
      SIGNAL(ShowAddWordsMainWindow()),
      add_words_main_window,
      SLOT(show()));

  connect(
      main_window,
      SIGNAL(ShowSelectBookMainWindow()),
      select_book_main_window,
      SLOT(show()));

  connect(
      select_book_main_window,
      SIGNAL(SelectResult(BookInfo)),
      bookshelf,
      SLOT(OnBookSelectResult(BookInfo)));

  connect(
      select_book_main_window,
      SIGNAL(SelectResult(BookInfo)),
      main_window,
      SLOT(OnBookSelectResult(BookInfo)));
  return true;
}

Factory::~Factory() {
  for (auto& obj : recycle_objects_) {
    delete obj;
  }
  for (auto& widget : recycle_widgets_) {
    delete widget;
  }
}
