#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include <QObject>
#include "book_info.h"
#include <QString>

class Bookshelf : public QObject
{
  Q_OBJECT
public:
  Bookshelf();
  std::vector<BookInfo> BookInfoList();
public slots:
  void OnBookSelection(const QString& book_name);
private:
  QString current_book_;
};

#endif // BOOKSHELF_H
