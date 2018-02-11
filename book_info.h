#ifndef BOOK_INFO_H
#define BOOK_INFO_H

#include <QString>

struct BookInfo
{
  BookInfo();
  QString name;
  QString summary;
  bool Empty();
};

#endif // BOOK_INFO_H
