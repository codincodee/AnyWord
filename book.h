#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include "book_info.h"

class Book
{
public:
  Book();
  bool Load(const QString& path);
  BookInfo GetBookInfo();
  static BookInfo Check(const QString& path);
  static bool Create(const QString& path, const BookInfo& info);
};

#endif // BOOK_H
