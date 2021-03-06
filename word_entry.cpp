#include "word_entry.h"

WordEntry::WordEntry()
{
  Clear();
}

bool WordEntry::Empty() const {
  return word.isEmpty();
}

void WordEntry::Clear() {
  word.clear();
  require_spelling = false;
  hit = 0;
  miss = 0;
}

//void WordEntry::UpdateNonHistoryComponents(
//    const WordEntry &from, WordEntry &to) {
//  to.word = from.word;
//  to.meaning = from.meaning;
//  to.note = from.note;
//  to.require_spelling = from.require_spelling;
//}
