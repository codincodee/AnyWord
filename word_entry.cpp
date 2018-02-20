#include "word_entry.h"

WordEntry::WordEntry()
  : require_spelling(false),
    hit(0),
    miss(0)
{

}

bool WordEntry::Empty() {
  return word.isEmpty();
}
