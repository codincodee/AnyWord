#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QObject>
#include "word_entry.h"
#include <QHash>
#include <set>

enum class MarkWordOperation {
  i_know, i_dont_know, reset
};

class Vocabulary : public QObject
{
  Q_OBJECT
public:
  Vocabulary();
  ~Vocabulary();
  bool PrepareWord(const WordEntry& entry);
  void PrintAll();
  void Clone(const Vocabulary& obj);
  WordEntry OfferWord();
  WordEntry MarkWord(const QString& word, const bool& know);
  WordEntry MarkWord(const QString &word, const MarkWordOperation &operation);
  struct ChronoEntry {
    ChronoEntry(WordEntry* entry);
    WordEntry* entry = nullptr;
  };
  inline int WordNum() const {
    return vocabulary_.size();
  }
  void Clear();
private:
  static bool IfMastered(const WordEntry& entry);
  static bool IfWeakMastered(
      const WordEntry& now,
      const QString& prev_hit_ts, const QString& prev_miss_ts);
  void ClearStorage();
  static void FixChronology(std::multiset<ChronoEntry>& chronology);
  QHash<QString, WordEntry*> vocabulary_;
  std::multiset<ChronoEntry> chronology_;
  std::vector<WordEntry*> offer_list_;
  int current_index_;
};

bool operator <(
    const Vocabulary::ChronoEntry& e1, const Vocabulary::ChronoEntry& e2);
#endif // VOCABULARY_H
