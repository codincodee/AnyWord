#ifndef WORD_ENTRY_H
#define WORD_ENTRY_H

#include <QString>
#include "book_info.h"

struct WordEntry
{
  WordEntry();
  QString word;
  QString meaning;
  QString note;
  int hit;
  int miss;

  bool Empty();
};

#endif // WORD_ENTRY_H
