#include "bookshelf.h"
#include <QDebug>
#include <QMessageBox>
#include "ui_utils.h"

using namespace std;

Bookshelf::Bookshelf()
{

}

void Bookshelf::OnBookSelection(const QString &book_name) {
  shared_ptr<Book> book(new Book);
  if (!book->Load(book_name)) {
    ShowWarning("No book found!");
    return;
  }
  current_book_ = book;
  emit CurrentBookChanged(book->GetBookInfo());
}

shared_ptr<Book> Bookshelf::CurrentBook() {
  return current_book_;
}

BookInfo Bookshelf::SearchBook(const QString &book) {
  BookInfo info;
  info.name = book;
  info.summary = book;
  return info;
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
