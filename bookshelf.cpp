#include "bookshelf.h"
#include <QDebug>
#include <QMessageBox>
#include "ui_utils.h"
#include <QFile>
#include <QDir>

using namespace std;

Bookshelf::Bookshelf()
{

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
  current_book_ = book;
  emit CurrentBookChanged(book->GetBookInfo());
}

shared_ptr<Book> Bookshelf::CurrentBook() {
  return current_book_;
}

QString Bookshelf::BookPath(const QString &name) {
  return bookshelf_path_ + "/" + name;
}

bool Bookshelf::CreateBook(const BookInfo& info) {
  return Book::Create(BookPath(info.name), info);
}

bool Bookshelf::DeleteBook(const QString &name) {
  return QDir(BookPath(name)).removeRecursively();
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
