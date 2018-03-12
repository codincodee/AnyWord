#include "vocabulary.h"
#include <QDebug>

Vocabulary::Vocabulary()
{
  current_index_ = 0;
}

Vocabulary::~Vocabulary() {
  ClearStorage();
}

void Vocabulary::LoadWord(const WordEntry &entry) {
  auto vo_i = vocabulary_.find(entry.word);
  if (vo_i == vocabulary_.end()) {
    auto entry_addr = new WordEntry(entry);
    entry_pool_.push_back(entry_addr);
    vocabulary_.insert(entry.word, entry_addr);
  } else {
    *(*vo_i) = entry;
  }
}

void Vocabulary::PrintAll() {
//  for (auto& entry : vocabulary_) {
//    qDebug() << entry.word << entry.meaning << entry.note << entry.hit << entry.miss;
//  }
}


void Vocabulary::Clone(const Vocabulary &obj) {
  ClearStorage();
  for (auto& entry_addr : obj.entry_pool_) {
    if (entry_addr->Empty()) {
      continue;
    }
    entry_pool_.push_back(new WordEntry(*entry_addr));
  }
  for (auto& entry_addr : entry_pool_) {
    vocabulary_.insert(entry_addr->word, entry_addr);
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
  auto vo_i = vocabulary_.find(entry.word);
  if (vo_i == vocabulary_.end()) {
    return WordEntry();
  } else {
    return *(*vo_i);
  }
}

WordEntry Vocabulary::MarkWord(const QString &word, const bool &know) {
  auto vo_i = vocabulary_.find(word);
  if (vo_i == vocabulary_.end()) {
    return WordEntry();
  }
  if (know) {
    ++((*vo_i)->hit);
    (*vo_i)->hit_ts = QDateTime::currentDateTime().toString();
  } else {
    ++((*vo_i)->miss);
    (*vo_i)->miss_ts = QDateTime::currentDateTime().toString();
  }
  return *(*vo_i);
}

bool Vocabulary::DeleteWord(const QString &word) {
  auto vo_i = vocabulary_.find(word);
  if (vo_i == vocabulary_.end()) {
    return true;
  }
  (*vo_i)->Clear();
  vocabulary_.remove(word);
  return true;
}

void Vocabulary::ClearStorage() {
  for (auto& entry_addr : entry_pool_) {
    delete entry_addr;
    entry_addr = nullptr;
  }
  entry_pool_.clear();
  vocabulary_.clear();
}
