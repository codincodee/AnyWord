#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include "book_info.h"
#include "vocabulary.h"
#include <memory>

class Book
{
public:
  Book();
  bool Load(const QString& path);
  BookInfo GetBookInfo();
  static BookInfo Check(const QString& path);
  static bool Create(const QString& path, const BookInfo& info);
private:
  std::shared_ptr<Vocabulary> vocabulary_;
  BookInfo information_;
};

#endif // BOOK_H
