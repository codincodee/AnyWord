#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include "book_info.h"

class Book
{
public:
  Book();
  bool Load(const QString& name);
  BookInfo GetBookInfo();
};

#endif // BOOK_H
