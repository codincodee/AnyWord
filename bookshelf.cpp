#include "bookshelf.h"
#include <QDebug>
#include <QMessageBox>
#include "ui_utils.h"
#include <QFile>
#include <QDir>
#include <QThread>
#include <QSettings>

using namespace std;

const QString kLastOpenBookIniKey = "last_open_book";

Bookshelf::Bookshelf()
{

}

Bookshelf::~Bookshelf() {
  QSettings settings(ini_file_path_, QSettings::IniFormat);
  settings.setValue(kLastOpenBookIniKey, current_book_name_);
}

bool Bookshelf::Init() {
  bookshelf_path_ = "./books";
  return true;
}

void Bookshelf::OnBookSelection(const QString &book_name) {
  shared_ptr<Book> book(new Book);
  if (!book->Load(BookPath(book_name))) {
    warn("No book found!");
    return;
  }
  current_book_name_ = book_name;
  emit ChangeBook(book);
  emit CurrentBookChanged(book->GetBookInfo());
}


bool Bookshelf::OpenBookFromHistory() {
  QSettings settings(ini_file_path_, QSettings::IniFormat);
  auto book = settings.value(kLastOpenBookIniKey).toString();
  if (book.isEmpty()) {
    return false;
  }
  OnBookSelection(book);
  return true;
}

QString Bookshelf::BookPath(const QString &name) {
  return bookshelf_path_ + "/" + name;
}

bool Bookshelf::CreateBook(const BookInfo& info) {
  return Book::Create(BookPath(info.name), info);
}

bool Bookshelf::DeleteBook(const QString &name) {
  return Book::Delete(BookPath(name));
}

BookInfo Bookshelf::SearchBook(const QString &name) {
  return Book::Check(BookPath(name));
}

vector<BookInfo> Bookshelf::BookInfoList() {
  auto books = QDir(bookshelf_path_).entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
  vector<BookInfo> list;
  for (auto& book : books) {
    BookInfo info = SearchBook(book.fileName());
    if (!info.Empty()) {
      list.push_back(info);
    }
  }
  return list;
}
