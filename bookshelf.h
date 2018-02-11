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
  void OnBookSelection(const QString& book_name);
};

#endif // BOOKSHELF_H
