#include "database.h"
#include <QDebug>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFile>
#include <QDir>

using namespace std;

Database::Database()
{

}

bool Database::Init() {
  return true;
}

QString Database::DBFileName() {
  return "book.db";
}

bool Database::NewDB(const QString& path, const BookInfo& info) {
  QSqlDatabase db;
  if (QSqlDatabase::contains()) {
    db = QSqlDatabase::database(
        QLatin1String(QSqlDatabase::defaultConnection), false);
  } else {
    db = QSqlDatabase::addDatabase("QSQLITE");
  }
  db.setDatabaseName(path + "/" + DBFileName());
  if (!db.open()) {
    return false;
  }
  QSqlQuery query;
  query.prepare("CREATE TABLE manifest (id INTEGER UNIQUE PRIMARY KEY, language VARCHAR(50), version VARCHAR(10))");
  if (!query.exec()) {
    qDebug() << query.lastError();
    db.close();
    return false;
  }

  query.prepare("INSERT INTO manifest (id, language, version) VALUES(1, '" + SupportLanguageToString(info.language) + "', 'v1.0.0')");
  if (!query.exec()) {
    qDebug() << query.lastError();
    db.close();
    return false;
  }

  query.prepare(
      "CREATE TABLE vocabulary ("
      "  word VARCHAR(100) UNIQUE PRIMARY KEY,"
      "  meaning VARCHAR(300),"
      "  note VARCHAR(1000),"
      "  hit INTEGER DEFAULT(0),"
      "  miss INTEGER DEFAULT(0),"
      "  require_spelling INTEGER DEFAULT(0)"
      ")");
  if (!query.exec()) {
    qDebug() << query.lastError();
    db.close();
    return false;
  }

  if (info.language == SupportLanguage::Korean) {
    query.prepare(
        "INSERT INTO vocabulary ("
        "  word,"
        "  meaning,"
        "  note,"
        "  hit,"
        "  miss"
        ")"
        "VALUES ("
        "  'the word A', 'the meaning', 'the note', 2, 1)");
    if (!query.exec()) {
      qDebug() << query.lastError();
    }
  }

  query.prepare("INSERT INTO vocabulary (word, meaning, note, hit, miss) VALUES('the word', 'the meaning', 'the note', 0, 0)");
  if (!query.exec()) {
    qDebug() << query.lastError();
  }

//  query.prepare("SELECT language FROM info WHERE id = 1");
//  if (!query.exec()) {
//    qDebug() << query.lastError();
//    db.close();
//    return false;
//  } else {
//    query.next();
//    QWidget widget;
//    QMessageBox::information(&widget, "test", query.value(0).toString());
//  }

//  query.prepare("SELECT COUNT(*) FROM entry");
//  if (!query.exec()) {
//    qDebug() << query.lastError();
//  } else {
//    query.next();
//    qDebug() << "Num:" << query.value(0).toInt();
//  }
  db.close();
  return true;
}

BookInfo Database::ReadBookInfoFromDB(const QString &path) {
  BookInfo info;
  info.name = QDir(path).dirName();
  auto path_to_file = path + "/" + DBFileName();
  if (!QFile(path_to_file).exists()) {
    return BookInfo();
  }
  QSqlDatabase db;
  if (QSqlDatabase::contains()) {
    db = QSqlDatabase::database(
        QLatin1String(QSqlDatabase::defaultConnection), false);
  } else {
    db = QSqlDatabase::addDatabase("QSQLITE");
  }
  db.setDatabaseName(path + "/" + DBFileName());
  if (!db.open()) {
    return BookInfo();
  }
  QSqlQuery query;
  query.prepare("SELECT language FROM manifest WHERE id = 1");
  if (!query.exec()) {
    qDebug() << query.lastError();
    db.close();
    return BookInfo();
  } else {
    query.next();
    info.language = StringToSupportLanguage(query.value(0).toString());
  }

  query.prepare("SELECT COUNT(*) FROM vocabulary");
  if (!query.exec()) {
    qDebug() << query.lastError();
    db.close();
    return BookInfo();
  } else {
    query.next();
    info.word_num = query.value(0).toInt();
  }
  db.close();
  return info;
}

shared_ptr<Vocabulary> Database::LoadVocabulary(const QString &path) {
  auto path_to_file = path + "/" + DBFileName();
  if (!QFile(path_to_file).exists()) {
    return shared_ptr<Vocabulary>();
  }
  QSqlDatabase db;
  if (QSqlDatabase::contains()) {
    db = QSqlDatabase::database(
        QLatin1String(QSqlDatabase::defaultConnection), false);
  } else {
    db = QSqlDatabase::addDatabase("QSQLITE");
  }
  db.setDatabaseName(path_to_file);
  if (!db.open()) {
    return shared_ptr<Vocabulary>();
  }
  shared_ptr<Vocabulary> vocabulary(new Vocabulary);
  QSqlQuery query;
  query.prepare(
      "SELECT"
      "  word,"
      "  meaning,"
      "  note,"
      "  hit,"
      "  miss,"
      "  require_spelling "
      "FROM vocabulary");
  if (query.exec()) {
    for (int row = 0; query.next(); ++row) {
      WordEntry entry;
      entry.word = query.value(0).toString();
      entry.meaning = query.value(1).toString();
      entry.note = query.value(2).toString();
      entry.hit = query.value(3).toInt();
      entry.miss = query.value(4).toInt();
      entry.require_spelling = query.value(5).toInt();
      vocabulary->LoadWord(entry);
    }
  } else {
    qDebug() << query.lastError();
    db.close();
    return shared_ptr<Vocabulary>();
  }
  db.close();
  return vocabulary;
}
