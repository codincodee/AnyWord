#include "book.h"

Book::Book()
{

}

bool Book::Load(const QString &name) {
  return false;
}

BookInfo Book::GetBookInfo() {
  BookInfo info;
  info.name = "new Book";
  info.summary = "What is this?";
  return info;
}
