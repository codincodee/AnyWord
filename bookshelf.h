#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include <QObject>
#include "book_info.h"

class Bookshelf : public QObject
{
  Q_OBJECT
public:
  Bookshelf();

public slots:
  void OnBookSelectResult(const BookInfo& book);
};

#endif // BOOKSHELF_H
