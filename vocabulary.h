#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QObject>
#include "word_entry.h"
#include <QHash>
#include <list>

class Vocabulary : public QObject
{
  Q_OBJECT
public:
  Vocabulary();
  ~Vocabulary();
  void LoadWord(const WordEntry& entry);
  void PrintAll();
  void Clone(const Vocabulary& obj);
  WordEntry GetWord();
  WordEntry Lookup(const WordEntry& entry);
  WordEntry MarkWord(const QString& word, const bool& know);
  bool DeleteWord(const QString& word);
private:
  void ClearStorage();
  QHash<QString, WordEntry*> vocabulary_;
  std::list<WordEntry*> entry_pool_;
  int current_index_;
};

#endif // VOCABULARY_H
