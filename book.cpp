#include "book.h"
#include <QFile>
#include <QDir>
#include <QDebug>

Book::Book()
{

}

bool Book::Load(const QString &path) {
  return false;
}

BookInfo Book::GetBookInfo() {
  BookInfo info;
  info.name = "new Book";
  info.summary = "What is this?";
  return info;
}

BookInfo Book::Check(const QString& path) {
  qDebug() << __LINE__;
  BookInfo info;
  qDebug() << __LINE__;
  if (!QDir(path).exists()) {
    qDebug() << __LINE__;
    return info;
  }
  qDebug() << __LINE__;
  QFile file(path + "/manifest.txt");
  qDebug() << path + "/manifest.txt";
  qDebug() << __LINE__;
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << __LINE__;
    return info;
  }
  qDebug() << __LINE__;
  info.name = QDir(path).dirName();
  qDebug() << __LINE__ << " " << info.name;
  auto raw = file.readAll();
  qDebug() << __LINE__ << raw.size();
  info.summary = QString::fromLocal8Bit(raw.data(), raw.size());
  qDebug() << __LINE__ << " " << info.summary;
  file.close();
  qDebug() << __LINE__;
  return info;
}
