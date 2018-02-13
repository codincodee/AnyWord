#include "factory.h"
#include "main_window.h"
#include "database.h"
#include "add_words_main_window.h"
#include "select_book_main_window.h"
#include "bookshelf.h"

using namespace std;

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
  bookshelf->Init();
  recycle_objects_.push_back(bookshelf);

  auto current_book = new Book;
  recycle_objects_.push_back(current_book);

  select_book_main_window->RegisterBookListCallback(
      bind(&Bookshelf::BookInfoList, bookshelf));
  select_book_main_window->RegisterBookInfoCallback(
      [bookshelf](const QString& book){return bookshelf->SearchBook(book);});
  select_book_main_window->RegisterCreateBookCallback(
      bind(&Bookshelf::CreateBook, bookshelf, placeholders::_1));
  select_book_main_window->RegisterDeleteBookCallback(
      bind(&Bookshelf::DeleteBook, bookshelf, placeholders::_1));

  main_window->RegisterGetWordCallback(
      [current_book](){return current_book->GetVocabulary().GetWord();});

  connect(
      bookshelf,
      SIGNAL(ChangeBook(std::shared_ptr<Book>)),
      current_book,
      SLOT(OnChange(std::shared_ptr<Book>)));

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
      SIGNAL(SelectBook(QString)),
      main_window,
      SLOT(OnBookSelection(QString)));

  connect(
      select_book_main_window,
      SIGNAL(SelectBook(const QString&)),
      bookshelf,
      SLOT(OnBookSelection(const QString&)));

  connect(
      bookshelf,
      SIGNAL(CurrentBookChanged(BookInfo)),
      main_window,
      SLOT(OnCurrentBookChanged(BookInfo)));
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
