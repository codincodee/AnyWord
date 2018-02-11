#include "bookshelf.h"
#include <QDebug>

using namespace std;

Bookshelf::Bookshelf()
{

}

void Bookshelf::OnBookSelection(const QString &book_name) {
  current_book_ = book_name;
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
