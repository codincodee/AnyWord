#ifndef BOOK_INFO_H
#define BOOK_INFO_H

#include <QString>
#include "support_language.h"

struct BookInfo
{
  BookInfo();
  QString name;
  QString summary;
  bool Empty();
  SupportLanguage language;
  int word_num = 0;
};

#endif // BOOK_INFO_H
