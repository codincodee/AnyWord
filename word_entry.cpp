#include "word_entry.h"

WordEntry::WordEntry()
{
  Clear();
}

bool WordEntry::Empty() {
  return word.isEmpty();
}

void WordEntry::Clear() {
  word.clear();
  require_spelling = false;
  hit = 0;
  miss = 0;
}
