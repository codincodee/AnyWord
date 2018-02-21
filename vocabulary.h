#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QObject>
#include "word_entry.h"
#include <QHash>

class Vocabulary : public QObject
{
  Q_OBJECT
public:
  Vocabulary();
  void LoadWord(const WordEntry& entry);
  void PrintAll();
  void Clone(const Vocabulary& obj);
  WordEntry GetWord();
  WordEntry Lookup(const WordEntry& entry);
  bool MarkWord(const QString& word, const bool& know);

private:
  QHash<QString, WordEntry> vocabulary_;
  int current_index_;
};

#endif // VOCABULARY_H
