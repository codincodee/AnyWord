#ifndef WORD_ENTRY_H
#define WORD_ENTRY_H

#include <QString>
#include "book_info.h"
#include <QDateTime>

struct WordEntry
{
  WordEntry();
  QString word;
  QString meaning;
  QString note;
  int hit;
  QString hit_ts; // time stamp
  int miss;
  QString miss_ts;
  bool require_spelling;

  bool Empty() const;
  void Clear();
  // static void UpdateNonHistoryComponents(const WordEntry& from, WordEntry& to);
};

#endif // WORD_ENTRY_H
