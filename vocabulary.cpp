#include "vocabulary.h"
#include <QDebug>

Vocabulary::Vocabulary()
{
  current_index_ = 0;
}

void Vocabulary::LoadWord(const WordEntry &entry) {
  auto vo_i = vocabulary_.find(entry.word);
  if (vo_i == vocabulary_.end()) {
    auto entry_addr = new WordEntry(entry);
    entry_pool_.push_back(entry_addr);
    vocabulary_[entry.word] = entry_addr;
  } else {
    *(vocabulary_[entry.word]) = entry;
  }
}

void Vocabulary::PrintAll() {
//  for (auto& entry : vocabulary_) {
//    qDebug() << entry.word << entry.meaning << entry.note << entry.hit << entry.miss;
//  }
}


void Vocabulary::Clone(const Vocabulary &obj) {
  for (auto& entry_addr : obj.entry_pool_) {
    if (entry_addr->Empty()) {
      continue;
    }
    entry_pool_.push_back(new WordEntry(*entry_addr));
  }
  for (auto& entry_addr : obj.entry_pool_) {
    vocabulary_[entry_addr->word] = entry_addr;
  }
}

WordEntry Vocabulary::GetWord() {
  if (vocabulary_.size() <= 0) {
    return WordEntry();
  }
  WordEntry entry;
  if (current_index_ < vocabulary_.size()) {
    entry = *(*(vocabulary_.begin() + current_index_));
  } else {
    current_index_ = 0;
    entry = *(*(vocabulary_.begin() + current_index_));
  }
  ++current_index_;
  return entry;
}

WordEntry Vocabulary::Lookup(const WordEntry &entry) {
  auto i = vocabulary_.find(entry.word);
  if (i == vocabulary_.end()) {
    return WordEntry();
  } else {
    return *(*i);
  }
}

WordEntry Vocabulary::MarkWord(const QString &word, const bool &know) {
  auto i = vocabulary_.find(word);
  if (i == vocabulary_.end()) {
    return WordEntry();
  }
  if (know) {
    ++(*i)->hit;
    (*i)->hit_ts = QDateTime::currentDateTime().toString();
  } else {
    ++(*i)->miss;
    (*i)->miss_ts = QDateTime::currentDateTime().toString();
  }
  return *(*i);
}

bool Vocabulary::DeleteWord(const QString &word) {
  auto i = vocabulary_.find(word);
  if (i == vocabulary_.end()) {
    return true;
  }
  (*i)->Clear();
  vocabulary_.remove(word);
  return true;
}
