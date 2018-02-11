#include "book.h"

Book::Book()
{

}

bool Book::Load(const QString &path) {
  return false;
}

BookInfo Book::GetBookInfo() {
  BookInfo info;
  info.name = "new Book";
  info.summary = "What is this?";
  return info;
}

BookInfo Book::Check(const QString& name) {
  BookInfo info;
  info.name = name;
  info.summary = name + "/" + name;
  return info;
}
