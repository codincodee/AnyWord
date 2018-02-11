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
  bookshelf_path_ = ".";
  return true;
}

void Bookshelf::OnBookSelection(const QString &book_name) {
  shared_ptr<Book> book(new Book);
  if (!book->Load(BookPath(book_name))) {
    ShowWarning("No book found!");
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

BookInfo Bookshelf::SearchBook(const QString &name) {
  return Book::Check(BookPath(name));
}

vector<BookInfo> Bookshelf::BookInfoList() {
  vector<BookInfo> list;
  BookInfo book;
  book.name = "A";
  list.push_back(book);
  book.name = "B";
  list.push_back(book);
  return list;
}
