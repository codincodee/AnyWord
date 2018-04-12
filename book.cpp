#include "book.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include "database.h"

Book::Book()
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
  vocabulary_ = Database::LoadVocabulary(path);
  if (vocabulary_) {
    vocabulary_->PrintAll();
    information_ = Database::ReadBookInfoFromDB(path);
    path_ = path;
  }
  return vocabulary_ != nullptr;
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

bool Book::MarkWord(const QString &word, const bool& know) {
  auto entry = vocabulary_->MarkWord(word, know);
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
