#include "vocabulary.h"
#include <QDebug>
#include <QDateTime>

Vocabulary::Vocabulary()
{
  current_index_ = 0;
}

Vocabulary::~Vocabulary() {
  ClearStorage();
}

bool Vocabulary::PrepareWord(const WordEntry &entry) {
  auto vo_i = vocabulary_.find(entry.word);
  if (vo_i == vocabulary_.end()) {
    auto entry_addr = new WordEntry(entry);
    vocabulary_.insert(entry.word, entry_addr);
    chronology_.insert(ChronoEntry(entry_addr));
    return true;
  } else {
    return false;
  }
}

//bool Vocabulary::UpdateWordNonHistoryComponents(const WordEntry &entry) {
//  auto vo_i = vocabulary_.find(entry.word);
//  if (vo_i == vocabulary_.end()) {
//    return false;
//  } else {
//    WordEntry::UpdateNonHistoryComponents(entry, *(*vo_i));
//    return true;
//  }
//}

void Vocabulary::PrintAll() {
//  for (auto& entry : vocabulary_) {
//    qDebug() << entry.word << entry.meaning << entry.note << entry.hit << entry.miss;
//  }
}


void Vocabulary::Clone(const Vocabulary &obj) {
  ClearStorage();
  for (auto& entry_addr : obj.vocabulary_) {
    if (!entry_addr) {
      continue;
    }
    if (entry_addr->Empty()) {
      continue;
    }
    auto new_entry_addr = new WordEntry(*entry_addr);
    vocabulary_.insert(new_entry_addr->word, new_entry_addr);
    chronology_.insert(ChronoEntry(new_entry_addr));
  }
//  for (auto& i : chronology_) {
//    qDebug() << i.entry->word << i.entry->miss_ts;
//  }
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

//bool Vocabulary::DeleteWord(const QString &word) {
//  auto vo_i = vocabulary_.find(word);
//  if (vo_i == vocabulary_.end()) {
//    return true;
//  }
//  (*vo_i)->Clear();
//  // vocabulary_.remove(word);
//  return true;
//}

void Vocabulary::ClearStorage() {
  for (auto& entry_addr : vocabulary_) {
    delete entry_addr;
  }
  vocabulary_.clear();
  chronology_.clear();
}

void Vocabulary::Clear() {
  ClearStorage();
}

Vocabulary::ChronoEntry::ChronoEntry(WordEntry* en) : entry(en) {}

bool operator<(
    const Vocabulary::ChronoEntry& e1, const Vocabulary::ChronoEntry& e2) {
  if (e1.entry == nullptr && e2.entry != nullptr) {
    return false;
  } else if (e1.entry != nullptr && e2.entry == nullptr) {
    return true;
  } else if (e1.entry == nullptr && e2.entry == nullptr) {
    return false;
  }

  if (e1.entry->miss_ts.isEmpty() && !e2.entry->miss_ts.isEmpty()) {
    return false;
  } else if (!e1.entry->miss_ts.isEmpty() && e2.entry->miss_ts.isEmpty()) {
    return true;
  } else if (e1.entry->miss_ts.isEmpty() && e2.entry->miss_ts.isEmpty()) {
    return false;
  }
  return
      QDateTime::fromString(e1.entry->miss_ts) >
      QDateTime::fromString(e2.entry->miss_ts);
}
