#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include "book_info.h"
#include "vocabulary.h"
#include <memory>
#include "object_base.h"

class Book : public ObjectBase
{
  Q_OBJECT
public:
  Book();
  BookInfo GetBookInfo();
  static BookInfo Check(const QString& path);
  static bool Create(const QString& path, const BookInfo& info);
  void Clone(const Book& obj);
  bool Load(const QString &path);
  Vocabulary& GetVocabulary();
  bool WriteEntry(const WordEntry& entry);
public slots:
  void OnChange(std::shared_ptr<Book> new_book);
private:
  std::shared_ptr<Vocabulary> vocabulary_;
  BookInfo information_;
  QString path_;
};

#endif // BOOK_H
