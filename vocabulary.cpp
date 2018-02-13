#include "vocabulary.h"
#include <QDebug>

Vocabulary::Vocabulary()
{

}

void Vocabulary::LoadWord(const WordEntry &entry) {
  vocabulary_[entry.word] = entry;
}

void Vocabulary::PrintAll() {
//  for (auto& entry : vocabulary_) {
//    qDebug() << entry.word << entry.meaning << entry.note << entry.hit << entry.miss;
//  }
}


void Vocabulary::Clone(const Vocabulary &obj) {
  vocabulary_ = obj.vocabulary_;
}

WordEntry Vocabulary::GetWord() {
  if (vocabulary_.size()) {
//    qDebug() << qrand();
    return *(vocabulary_.begin() + (qrand() % 10 > 5 ? 0 : 1));
  }
  return WordEntry();
}

WordEntry Vocabulary::Lookup(const WordEntry &entry) {
  auto i = vocabulary_.find(entry.word);
  if (i == vocabulary_.end()) {
    return WordEntry();
  } else {
    return *i;
  }
}
