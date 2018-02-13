#include "book.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include "database.h"

Book::Book()
{

}

void Book::Clone(const Book &obj) {
  if (obj.vocabulary_) {
    vocabulary_.reset(new Vocabulary);
    vocabulary_->Clone(*obj.vocabulary_);
  }
  information_ = obj.information_;
  path_ = obj.path_;
}

void Book::OnChange(std::shared_ptr<Book> new_book) {
  this->Clone(*new_book);
}

bool Book::Load(const QString &path) {
  qDebug() << __LINE__;
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
  return Database::WriteEntry(entry, path_);
}

BookInfo Book::GetBookInfo() {
  return information_;
}

BookInfo Book::Check(const QString& path) {
  BookInfo info;
  if (!QDir(path).exists()) {
    return info;
  }
//  QFile file(path + "/manifest.txt");
//  if (!file.open(QIODevice::ReadOnly)) {
//    return info;
//  }
//  info.name = QDir(path).dirName();
//  auto raw = file.readAll();
//  info.summary = QString::fromLocal8Bit(raw.data(), raw.size());
//  file.close();
  return Database::ReadBookInfoFromDB(path);
}

bool Book::Create(const QString& path, const BookInfo& info) {
  if (!QDir().mkpath(path)) {
    return false;
  }
//  QFile file(path + "/manifest.txt");
//  if (!file.open(QIODevice::WriteOnly)) {
//    return false;
//  }
//  QTextStream ts(&file);
//  ts << "lala" << endl;
//  file.close();
  return Database::NewDB(path, info);
}
