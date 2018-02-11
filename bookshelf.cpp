#include "bookshelf.h"
#include <QDebug>

Bookshelf::Bookshelf()
{

}

void Bookshelf::OnBookSelection(const QString &book_name) {
  qDebug() << book_name;
}
