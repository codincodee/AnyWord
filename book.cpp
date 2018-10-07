#include "book.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include "database.h"
#include "media_manager.h"

Book::Book() : kVolumeFolderName("volumes")
{

}

bool Book::Init() {
  vocabulary_.reset(new Vocabulary);
  return true;
}

void Book::Clone(const Book &obj) {
  if (obj.vocabulary_) {
    vocabulary_.reset(new Vocabulary);
    vocabulary_->Clone(*obj.vocabulary_);
  }
  information_ = obj.information_;
  path_ = obj.path_;
  // qDebug() << Database::ClearHistory(path_);
}

void Book::OnChange(std::shared_ptr<Book> new_book) {
  this->Clone(*new_book);
}

void Book::OnPlayRecord(const QString &word) {
  if (path_.isEmpty()) {
    warn("Book path is null, unable to play record!");
    return;
  }
  emit PlayRecord(path_ + "/" + word);
}

void Book::OnSaveRecord(const QString &word) {
  if (path_.isEmpty()) {
    warn("Book path is null, unable to save record!");
    return;
  }
  emit SaveRecord(path_ + "/" + word);
}

void Book::OnLoadRecord(const QString &word) {
  if (path_.isEmpty()) {
    warn("Book path is null, unable to load record!");
    return;
  }
  emit LoadRecord(path_ + "/" + word);
}

void Book::OnDeleteRecord(const QString &word) {
  if (path_.isEmpty()) {
    warn("Book path is null, unable to delete record!");
    return;
  }
  emit DeleteRecord(path_ + "/" + word);
}

bool Book::Load(const QString &path) {
//  vocabulary_ = Database::LoadVocabulary(path);
//  if (vocabulary_) {
//    vocabulary_->PrintAll();
//    information_ = Database::ReadBookInfoFromDB(path);
//    path_ = path;
//    auto volume_path = LoadVolume(path);
//  }
  auto information = Database::ReadBookInfoFromDB(path);
  if (information.Empty()) {
    return false;
  }
  information_ = information;
  auto volume_path = LoadVolume(path);
  if (volume_path.isEmpty()) {
    return false;
  }
  information = Database::ReadBookInfoFromDB(volume_path);
  if (information.Empty()) {
    return false;
  }
  information_ = information;
  auto vocabulary = Database::LoadVocabulary(volume_path);
  if (!vocabulary) {
    return false;
  }
  vocabulary_ = vocabulary;
  path_ = volume_path;
//  return vocabulary_ != nullptr;
  return true;
}

QString Book::LoadVolume(const QString &path) {
  auto volume_path = path + "/" + kVolumeFolderName;
  // no volume
  if (!QDir(volume_path).exists() || QDir(volume_path).isEmpty()) {
    QDir book_dir(path);
    book_dir.mkdir(kVolumeFolderName);
    if (!QDir(volume_path).exists()) {
      return "";
    }
    if (!BuildVolume(path, volume_path)) {
      return "";
    }
  }
  auto dirs = QDir(volume_path);
  auto dir_names = dirs.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
  if (dir_names.isEmpty()) {
    return false;
  }
  return volume_path + "/" + dir_names[0];
}

bool Book::BuildVolume(const QString &book_path, const QString &volumes_path) {
//  if (!Database::ClearHistory(book_path)) {
//    return false;
//  }
  auto vocabulary = Database::LoadVocabulary(book_path);
  if (!vocabulary) {
    return false;
  }
  auto volumes = vocabulary->GenerateVolumes();
  if (volumes.empty()) {
    return false;
  }
  int cnt = 1;
  QDir volumes_dir(volumes_path);
  for (auto& volume : volumes) {
    auto volume_folder = information_.name + "-" + QString::number(cnt);
    auto volume_path = volumes_path + "/" + volume_folder;
    if (!volumes_dir.mkdir(volume_folder)) {
      return false;
    }
    auto information = information_;
    information.name += "-" + QString::number(cnt);
    information.word_num = volume->WordNum();
    if (!Book::Create(volume_path, information)) {
      return false;
    }
    for (auto& word : volume->vocabulary_) {
      if (!Database::WriteEntry(*word, volume_path)) {
        return false;
      }
      QString audio = word->word + MediaManager::AudioFileSuffix();
      QFile::copy(book_path + "/" + audio, volume_path + "/" + audio);
    }
    ++cnt;
  }
  return true;
}

Vocabulary& Book::GetVocabulary() {
  return *vocabulary_;
}

bool Book::WriteEntry(const WordEntry &entry) {
  // TODO: make sure that the book is closed
  if (vocabulary_->WordNum()) {
    qDebug() << "Close the book before writing an entry.";
    return false;
  }
  // vocabulary_->UpdateWordNonHistoryComponents(entry);
  // emit SaveRecord(path_ + "/" + entry.word);
  bool success = Database::WriteEntry(entry, path_);
  if (!success) {
    warn("Fail to write an entry");
  }
  return success;
}

void Book::OnDeleteEntry(const QString &word) {
  // vocabulary_->DeleteWord(word);
  // TODO: make sure that the book is closed
  if (vocabulary_->WordNum()) {
    qDebug() << "Close the book before deleting an entry";
    return;
  }
  Database::DeleteEntry(word, path_);
}

void Book::OnCloseSignal() {
  vocabulary_->Clear();
}

BookInfo Book::GetBookInfo() {
  return information_;
}

BookInfo Book::Check(const QString& path) {
  BookInfo info;
  if (!QDir(path).exists()) {
    return info;
  }
  return Database::ReadBookInfoFromDB(path);
}

bool Book::Create(const QString& path, const BookInfo& info) {
  if (!QDir().mkpath(path)) {
    return false;
  }
  return Database::NewDB(path, info);
}

bool Book::Delete(const QString &path) {
  Database::CloseDB(path);
  return QDir(path).removeRecursively();
}

bool Book::MarkWord(const QString &word, const bool &know) {
  return MarkWord(
      word, know ? MarkWordOperation::i_know : MarkWordOperation::i_dont_know);
}

bool Book::ResetWord(const QString &word) {
  return MarkWord(word, MarkWordOperation::reset);
}

bool Book::MarkWord(const QString &word, const MarkWordOperation& operation) {
  auto entry = vocabulary_->MarkWord(word, operation);
  if (entry.Empty()) {
    return false;
  }
  bool success = Database::WriteEntry(entry, path_);
  if (!success) {
    warn("Unable to write an entry");
  }
  return success;
}

WordEntry Book::LookUp(const QString &word) {
  return Database::LookUp(word, path_);
}

bool Book::GetBookProgress(int &memorized, int &total) {
  total = information_.word_num;
  memorized = total - vocabulary_->WordNum();
  return true;
}
