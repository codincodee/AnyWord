#include "factory.h"
#include "main_window.h"
#include "database.h"
#include "add_words_main_window.h"
#include "select_book_main_window.h"
#include "bookshelf.h"
#include "media_manager.h"
#include "minimized_main_window.h"

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
  current_book->Init();
  recycle_objects_.push_back(current_book);

  auto media_manager = new MediaManager;
  media_manager->Init();
  recycle_objects_.push_back(media_manager);

  auto minimized_main_window_ = new MinimizedMainWindow;
  recycle_widgets_.push_back(minimized_main_window_);

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
  main_window->RegisterMarkWordCallback(
      [current_book](const QString& word, const bool& know){
        return current_book->MarkWord(word, know);});

  add_words_main_window->RegisterSearchBookCallback(
      [current_book](const WordEntry& entry){
        return current_book->GetVocabulary().Lookup(entry);});
  add_words_main_window->RegisterWriteEntryCallback(
      bind(&Book::WriteEntry, current_book, placeholders::_1));

  add_words_main_window->RegisterRecordExistsCallback(
      bind(&MediaManager::HasRecord, media_manager));

  connect(
      bookshelf,
      SIGNAL(ChangeBook(std::shared_ptr<Book>)),
      current_book,
      SLOT(OnChange(std::shared_ptr<Book>)));

  connect(
      main_window,
      SIGNAL(ShowAddWordsMainWindow()),
      add_words_main_window,
      SLOT(OnShow()));

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

  connect(
      add_words_main_window,
      SIGNAL(StartRecord()),
      media_manager,
      SLOT(OnStartRecord()));

  connect(
      add_words_main_window,
      SIGNAL(StopRecord()),
      media_manager,
      SLOT(OnStopRecord()));

  connect(
      add_words_main_window,
      SIGNAL(PlayRecord()),
      media_manager,
      SLOT(OnPlayRecord()));

//  connect(
//      current_book,
//      SIGNAL(SaveRecord(QString)),
//      media_manager,
//      SLOT(OnSaveRecord(QString)));

  connect(
      main_window,
      SIGNAL(Destroyed()),
      minimized_main_window_,
      SLOT(close()));

  connect(
      main_window,
      SIGNAL(SwitchMiniWindowOnOff()),
      minimized_main_window_,
      SLOT(OnSwitchWindow()));

  connect(
      minimized_main_window_,
      SIGNAL(CheckPushButtonClicked()),
      main_window,
      SLOT(on_IKnowTheWordPushButton_clicked()));

  connect(
      minimized_main_window_,
      SIGNAL(CrossPushButtonClicked()),
      main_window,
      SLOT(on_IDontKnowTheWordPushButton_clicked()));

  connect(
      minimized_main_window_,
      SIGNAL(PassPushButtonClicked()),
      main_window,
      SLOT(on_PassPushButton_clicked()));

  connect(
      main_window,
      SIGNAL(DisplayWordSignal(WordEntry)),
      minimized_main_window_,
      SLOT(OnDisplayWord(WordEntry)));

  connect(
      main_window,
      SIGNAL(DisplayWordMeaningSignal(WordEntry,bool)),
      minimized_main_window_,
      SLOT(OnDisplayWordMeaning(WordEntry,bool)));

  connect(
      main_window,
      SIGNAL(PlayRecord(QString)),
      current_book,
      SLOT(OnPlayRecord(QString)));

  connect(
      current_book,
      SIGNAL(PlayRecord(QString)),
      media_manager,
      SLOT(OnPlayRecord(QString)));

  connect(
      add_words_main_window,
      SIGNAL(SaveRecord(QString)),
      current_book,
      SLOT(OnSaveRecord(QString)));

  connect(
      current_book,
      SIGNAL(SaveRecord(QString)),
      media_manager,
      SLOT(OnSaveRecord(QString)));

  connect(
      add_words_main_window,
      SIGNAL(LoadRecord(QString)),
      current_book,
      SLOT(OnLoadRecord(QString)));

  connect(
      current_book,
      SIGNAL(LoadRecord(QString)),
      media_manager,
      SLOT(OnLoadRecord(QString)));

  connect(
      add_words_main_window,
      SIGNAL(ClearRecord()),
      media_manager,
      SLOT(OnClearRecord()));

  connect(
      add_words_main_window,
      SIGNAL(DeleteEntry(QString)),
      current_book,
      SLOT(OnDeleteEntry(QString)));

  connect(
      add_words_main_window,
      SIGNAL(DeleteRecord(QString)),
      current_book,
      SLOT(OnDeleteRecord(QString)));

  connect(
      current_book,
      SIGNAL(DeleteRecord(QString)),
      media_manager,
      SLOT(OnDeleteRecord(QString)));

  connect(
      main_window,
      SIGNAL(ModifyEntry(QString)),
      add_words_main_window,
      SLOT(OnLoadEntry(QString)));

  connect(
      add_words_main_window,
      SIGNAL(CloseBook()),
      main_window,
      SLOT(OnCloseBook()));

  connect(
      add_words_main_window,
      SIGNAL(CloseBook()),
      current_book,
      SLOT(OnCloseSignal()));
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
