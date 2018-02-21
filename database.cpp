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
      "  hit INTEGER,"
      "  hit_ts VARCHAR(30),"
      "  miss INTEGER,"
      "  miss_ts VARCHAR(30),"
      "  require_spelling INTEGER"
      ")");
  if (!query.exec()) {
    qDebug() << __FILE__ << __LINE__ << query.lastError();
    db.close();
    return false;
  }

//  if (info.language == SupportLanguage::Korean) {
//    query.prepare(
//        "INSERT INTO vocabulary ("
//        "  word,"
//        "  meaning,"
//        "  note,"
//        "  hit,"
//        "  hit_ts,"
//        "  miss,"
//        "  miss_ts,"
//        "  require_spelling"
//        ")"
//        "VALUES ("
//        "  'the word A',"
//        "  'the meaning',"
//        "  'the note',"
//        "  2,"
//        "  '',"
//        "  1,"
//        "  '',"
//        "  0)");
//    if (!query.exec()) {
//      qDebug() << query.lastError();
//    }
//  }

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
      "  hit_ts,"
      "  miss,"
      "  miss_ts,"
      "  require_spelling "
      "FROM vocabulary");
  if (query.exec()) {
    for (int row = 0; query.next(); ++row) {
      WordEntry entry;
      int i = 0;
      entry.word = query.value(i++).toString();
      entry.meaning = query.value(i++).toString();
      entry.note = query.value(i++).toString();
      entry.hit = query.value(i++).toInt();
      entry.hit_ts = query.value(i++).toString();
      entry.miss = query.value(i++).toInt();
      entry.miss_ts = query.value(i++).toString();
      entry.require_spelling = query.value(i++).toInt();
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

bool Database::WriteEntry(const WordEntry &entry, const QString &path) {
  auto path_to_file = path + "/" + DBFileName();
  if (!QFile(path_to_file).exists()) {
    return false;
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
    return false;
  }
  QSqlQuery query;
  query.prepare(
      "SELECT COUNT(*) FROM vocabulary "
      "WHERE word = '" + entry.word + "'");
  if (!query.exec()) {
    qDebug() << query.lastError();
    db.close();
    return false;
  }
  query.next();
  if (query.value(0).toInt() > 0) {
    query.prepare(
        "DELETE FROM vocabulary "
        "WHERE word = '" + entry.word + "'");
    if (!query.exec()) {
      qDebug() << query.lastError();
      db.close();
      return false;
    }
  }
  query.prepare(
      "INSERT INTO vocabulary ("
      "  word,"
      "  meaning,"
      "  note,"
      "  hit,"
      "  hit_ts,"
      "  miss,"
      "  miss_ts,"
      "  require_spelling"
      ") "
      "VALUES "
      "("
      "  '" + entry.word + "',"
      "  '" + entry.meaning + "',"
      "  '" + entry.note + "',"
      "  " + QString::number(entry.hit) + ","
      "  '" + entry.hit_ts + "',"
      "  " + QString::number(entry.miss) + ","
      "  '" + entry.miss_ts + "',"
      "  " + QString::number((int)entry.require_spelling) +
      ")");
  if (!query.exec()) {
    qDebug() << query.lastError();
    db.close();
    return false;
  }

  db.close();
  return true;
}
