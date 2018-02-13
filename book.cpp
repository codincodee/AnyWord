#include "book.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include "database.h"

Book::Book()
{

}

bool Book::Load(const QString &path) {
  vocabulary_ = Database::LoadVocabulary(path);
  qDebug() << (vocabulary_ != nullptr);
  if (vocabulary_) {
    vocabulary_->PrintAll();
  }
  return vocabulary_ != nullptr;
}

BookInfo Book::GetBookInfo() {
  BookInfo info;
  info.name = "new Book";
  info.summary = "What is this?";
  return info;
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
