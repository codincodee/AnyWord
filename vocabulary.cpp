#include "vocabulary.h"
#include <QDebug>

Vocabulary::Vocabulary()
{
  current_index_ = 0;
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
  if (vocabulary_.size() <= 0) {
    return WordEntry();
  }
  WordEntry entry;
  if (current_index_ < vocabulary_.size()) {
    entry = *(vocabulary_.begin() + current_index_);
  } else {
    current_index_ = 0;
    entry = *(vocabulary_.begin() + current_index_);
  }
  ++current_index_;
  return entry;
}

WordEntry Vocabulary::Lookup(const WordEntry &entry) {
  auto i = vocabulary_.find(entry.word);
  if (i == vocabulary_.end()) {
    return WordEntry();
  } else {
    return *i;
  }
}

bool Vocabulary::MarkWord(const QString &word, const bool &know) {
  auto i = vocabulary_.find(word);
  if (i == vocabulary_.end()) {
    return false;
  }
  if (know) {
    ++i->hit;
    i->hit_ts = QDateTime::currentDateTime().toString();
  } else {
    ++i->miss;
    i->miss_ts = QDateTime::currentDateTime().toString();
  }
  return true;
}
