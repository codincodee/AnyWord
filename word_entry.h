#ifndef WORD_ENTRY_H
#define WORD_ENTRY_H

#include <QString>

struct WordEntry
{
  WordEntry();
  QString word;
  QString meaning;
  QString note;

  bool Empty();
};

#endif // WORD_ENTRY_H
