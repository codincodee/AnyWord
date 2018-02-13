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
  bool Init();
  std::vector<BookInfo> BookInfoList();
  BookInfo SearchBook(const QString& book);
  QString BookPath(const QString& name);
  bool CreateBook(const BookInfo& info);
  bool DeleteBook(const QString& name);
signals:
  void CurrentBookChanged(const BookInfo& book);
  void ChangeBook(std::shared_ptr<Book> book);
public slots:
  void OnBookSelection(const QString& book_name);
private:
  QString bookshelf_path_;
};

#endif // BOOKSHELF_H
