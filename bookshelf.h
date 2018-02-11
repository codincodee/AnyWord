#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include <QObject>
#include "book_info.h"
#include <QString>
#include "book.h"
#include <QHash>
#include "object_base.h"
#include <memory>

class Bookshelf : public ObjectBase
{
  Q_OBJECT
public:
  Bookshelf();
  std::vector<BookInfo> BookInfoList();
  std::shared_ptr<Book> CurrentBook();
signals:
  void CurrentBookChanged(const BookInfo& book);
public slots:
  void OnBookSelection(const QString& book_name);
private:
  QHash<QString, std::shared_ptr<Book>> books_;
  std::shared_ptr<Book> current_book_;
};

#endif // BOOKSHELF_H
