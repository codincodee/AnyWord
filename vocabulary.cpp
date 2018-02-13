#include "vocabulary.h"
#include <QDebug>

Vocabulary::Vocabulary()
{

}

void Vocabulary::LoadWord(const WordEntry &entry) {
  vocabulary_[entry.word] = entry;
}

void Vocabulary::PrintAll() {
  for (auto& entry : vocabulary_) {
    qDebug() << entry.word << entry.meaning << entry.note << entry.hit << entry.miss;
  }
}
