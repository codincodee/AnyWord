#ifndef WORD_ENTRY_H
#define WORD_ENTRY_H

#include <QString>
#include "book_info.h"

struct WordEntry
{
  WordEntry();
  BookInfo book;
  QString word;
  QString meaning;
  QString note;

  bool Empty();
};

#endif // WORD_ENTRY_H
