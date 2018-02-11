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
  bookshelf->SetWidget(main_window);
  recycle_objects_.push_back(bookshelf);

  select_book_main_window->RegisterBookListCallback(
      bind(&Bookshelf::BookInfoList, bookshelf));
  select_book_main_window->RegisterBookInfoCallback([bookshelf](const QString& book){return bookshelf->CurrentBook()->GetBookInfo();});

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
      SIGNAL(SelectBook(const QString&)),
      bookshelf,
      SLOT(OnBookSelection(const QString&)));
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
