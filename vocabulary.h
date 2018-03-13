#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QObject>
#include "word_entry.h"
#include <QHash>
#include <set>

class Vocabulary : public QObject
{
  Q_OBJECT
public:
  Vocabulary();
  ~Vocabulary();
  bool PrepareWord(const WordEntry& entry);
  // bool UpdateWordNonHistoryComponents(const WordEntry& entry);
  void PrintAll();
  void Clone(const Vocabulary& obj);
  WordEntry GetWord();
  WordEntry Lookup(const WordEntry& entry);
  WordEntry MarkWord(const QString& word, const bool& know);
  // bool DeleteWord(const QString& word);
  struct ChronoEntry {
    ChronoEntry(WordEntry* entry);
    WordEntry* entry = nullptr;
  };
  inline int WordNum() const {
    return vocabulary_.size();
  }
  void Clear();
private:
  void ClearStorage();
  QHash<QString, WordEntry*> vocabulary_;
  std::multiset<ChronoEntry> chronology_;
  int current_index_;
};

bool operator <(
    const Vocabulary::ChronoEntry& e1, const Vocabulary::ChronoEntry& e2);
#endif // VOCABULARY_H
