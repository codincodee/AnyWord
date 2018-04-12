#include "vocabulary.h"
#include <QDebug>
#include <QDateTime>
#include <random>
#include <QFile>

Vocabulary::Vocabulary()
{
  current_index_ = 0;
}

Vocabulary::~Vocabulary() {
  ClearStorage();
}

bool Vocabulary::PrepareWord(const WordEntry &entry) {
  if (IfMastered(entry)) {
    return true;
  }
  auto vo_i = vocabulary_.find(entry.word);
  if (vo_i == vocabulary_.end()) {
    auto entry_addr = new WordEntry(entry);
    vocabulary_.insert(entry.word, entry_addr);
    chronology_.insert(ChronoEntry(entry_addr));
    return true;
  } else {
    qDebug() << "Detected an existing word in the vocabulary.";
    return false;
  }
}

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
//    qDebug() << i.entry->word << i.entry->hit_ts << i.entry->miss_ts;
//  }
//  QFile file("vocabulary.txt");
//  qDebug() << file.open(QIODevice::ReadWrite);
//  QTextStream stream(&file);
//  stream.setCodec("UTF-8");
//  for (auto& i : chronology_) {
//    stream << i.entry->word << " " << i.entry->hit << " " << i.entry->hit_ts << " " << i.entry->miss << " " << i.entry->miss_ts << "\n";
//  }
//  file.close();
}

WordEntry Vocabulary::OfferWord() {
  // No offer_list_
  if (offer_list_.empty()) {
    // Load offer_list_ until (1) offer_list_ > 30; (2) chronology_ used out
    for (auto& chrono_entry : chronology_) {
      if (!chrono_entry.entry) {
        continue;
      }
      if (IfMastered(*chrono_entry.entry)) {
        continue;
      }
      offer_list_.push_back(chrono_entry.entry);
      if (offer_list_.size() >= 40) {
        break;
      }
    }
  }

  if (offer_list_.empty()) {
    return WordEntry();
  }

  ++current_index_;
  if (current_index_ >= offer_list_.size() || current_index_ < 0) {
    current_index_ = 0;
  }
  return *offer_list_[current_index_];
}

WordEntry Vocabulary::MarkWord(const QString &word, const bool &know) {
  auto vo_i = vocabulary_.find(word);
  if (vo_i == vocabulary_.end()) {
    return WordEntry();
  }
  auto previous_hit_ts = (*vo_i)->hit_ts;
  auto previous_miss_ts = (*vo_i)->miss_ts;

  if (know) {
    (*vo_i)->miss = 0;
    ++((*vo_i)->hit);
    (*vo_i)->hit_ts = QDateTime::currentDateTime().toString();
  } else {
    (*vo_i)->hit = 0;
    ++((*vo_i)->miss);
    (*vo_i)->miss_ts = QDateTime::currentDateTime().toString();
    return *(*vo_i);
  }

  auto entry = *(*vo_i);
  if (IfWeakMastered(entry, previous_hit_ts, previous_miss_ts)) {
    int erased_offer_index = -1;
    for (int offer = 0; offer < offer_list_.size(); ++offer) {
      if (offer_list_[offer]->word == entry.word) {
        offer_list_.erase(offer_list_.begin() + offer);
        erased_offer_index = offer;
      }
    }
    FixChronology(chronology_);
    for (auto chrono = chronology_.rbegin();
         chrono !=chronology_.rend(); ++chrono) {
      if (IfMastered(*chrono->entry)) {
        continue;
      }
      bool existed = false;
      for (auto& offer : offer_list_) {
        if (offer->word == chrono->entry->word) {
          existed = true;
        }
      }
      if (existed) {
        continue;
      } else {
        if (erased_offer_index < 0) {
          qDebug() << __FILE__ << __LINE__;
        }
        offer_list_.insert(
            offer_list_.begin() + erased_offer_index, chrono->entry);
        break;
      }
    }
  }

  return *(*vo_i);
}

bool Vocabulary::IfMastered(const WordEntry &entry) {
  if (entry.hit >= 6) {
    return true;
  }
  auto hit =
      entry.hit_ts.isEmpty() ?
          QDateTime::fromSecsSinceEpoch(0) :
          QDateTime::fromString(entry.hit_ts);
  auto miss =
      entry.miss_ts.isEmpty() ?
          QDateTime::fromSecsSinceEpoch(0) :
          QDateTime::fromString(entry.miss_ts);
  if ((hit.toSecsSinceEpoch() - miss.toSecsSinceEpoch()) > 3600 * 24) {
    if (entry.hit >= 3) {
      return true;
    }
  }

  if ((hit.toSecsSinceEpoch() - miss.toSecsSinceEpoch()) > 3600) {
    if (entry.hit >= 4) {
      return true;
    }
  }
  return false;
}

bool Vocabulary::IfWeakMastered(
    const WordEntry &entry,
    const QString &prev_hit_ts, const QString &prev_miss_ts) {
  auto now_hit =
      entry.hit_ts.isEmpty() ?
          QDateTime::fromSecsSinceEpoch(0) :
          QDateTime::fromString(entry.hit_ts);
  auto now_miss =
      entry.miss_ts.isEmpty() ?
          QDateTime::fromSecsSinceEpoch(0) :
          QDateTime::fromString(entry.miss_ts);
  auto prev_hit =
      prev_hit_ts.isEmpty() ?
          QDateTime::fromSecsSinceEpoch(0) :
          QDateTime::fromString(prev_hit_ts);
  auto prev_miss =
      prev_miss_ts.isEmpty() ?
          QDateTime::fromSecsSinceEpoch(0) :
          QDateTime::fromString(prev_miss_ts);

  if (now_hit < now_miss) {
    return false;
  }
  if (prev_hit > prev_miss) {
    if ((now_hit.toSecsSinceEpoch() - prev_hit.toSecsSinceEpoch()) < 60 * 60) {
      if ((prev_hit.toSecsSinceEpoch() - prev_miss.toSecsSinceEpoch()) > 60 * 10) {
        return true;
      } else {
        if (entry.hit >= 3) {
          return true;
        }
      }
    }
  }
  return false;
}

void Vocabulary::ClearStorage() {
  for (auto& entry_addr : vocabulary_) {
    delete entry_addr;
  }
  vocabulary_.clear();
  chronology_.clear();
  offer_list_.clear();
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

  if (e1.entry->hit_ts.isEmpty() && e1.entry->miss_ts.isEmpty()) {
    return false;
  }
  if (e2.entry->hit_ts.isEmpty() && e2.entry->miss_ts.isEmpty()) {
    return true;
  }

  QDateTime stamp1, stamp2;
  if (e1.entry->hit_ts.isEmpty()) {
    stamp1 = QDateTime::fromString(e1.entry->miss_ts);
  } else if (e1.entry->miss_ts.isEmpty()) {
    stamp1 = QDateTime::fromString(e1.entry->hit_ts);
  } else {
    QDateTime hit, miss;
    hit = QDateTime::fromString(e1.entry->hit_ts);
    miss = QDateTime::fromString(e1.entry->miss_ts);
    stamp1 = (hit > miss) ? hit : miss;
  }

  if (e2.entry->hit_ts.isEmpty()) {
    stamp2 = QDateTime::fromString(e2.entry->miss_ts);
  } else if (e2.entry->miss_ts.isEmpty()) {
    stamp2 = QDateTime::fromString(e2.entry->hit_ts);
  } else {
    QDateTime hit, miss;
    hit = QDateTime::fromString(e2.entry->hit_ts);
    miss = QDateTime::fromString(e2.entry->miss_ts);
    stamp2 = (hit > miss) ? hit : miss;
  }

  return stamp1 > stamp2;
}

void Vocabulary::FixChronology(std::multiset<ChronoEntry> &chronology) {
  std::multiset<ChronoEntry> new_chronology;
  for (auto& chrono : chronology) {
    new_chronology.insert(chrono);
  }
  chronology = new_chronology;
}
