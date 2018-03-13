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

QSqlDatabase Database::q_sql_database_ = QSqlDatabase::addDatabase("QSQLITE");

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
  if (!KeepDBOpen(path + "/" + DBFileName(), q_sql_database_)) {
    return false;
  }
  QSqlQuery query;
  QString cmd;

  cmd =
      "CREATE TABLE manifest ("
      "  id INTEGER UNIQUE PRIMARY KEY,"
      "  language VARCHAR(50),"
      "  version VARCHAR(10))";
  query.prepare(cmd);
  if (!query.exec()) {
    qDebug() << cmd << query.lastError();
    return false;
  }

  cmd =
      "INSERT INTO manifest ("
      "  id,"
      "  language, "
      "  version)"
      "VALUES("
      "  1,"
      "  '" + SupportLanguageToString(info.language) + "',"
      "  'v1.0.0')";
  query.prepare(cmd);
  if (!query.exec()) {
    qDebug() << cmd << query.lastError();
    return false;
  }

  cmd =
      "CREATE TABLE vocabulary ("
      "  word VARCHAR(100) UNIQUE PRIMARY KEY,"
      "  meaning VARCHAR(300),"
      "  note VARCHAR(1000),"
      "  hit INTEGER,"
      "  hit_ts VARCHAR(30),"
      "  miss INTEGER,"
      "  miss_ts VARCHAR(30),"
      "  require_spelling INTEGER"
      ")";
  query.prepare(cmd);
  if (!query.exec()) {
    qDebug() << cmd << query.lastError();
    return false;
  }
  return true;
}

BookInfo Database::ReadBookInfoFromDB(const QString &path_to_dir) {
  BookInfo info;
  info.name = QDir(path_to_dir).dirName();
  auto path_to_file = path_to_dir + "/" + DBFileName();
  if (!QFile(path_to_file).exists()) {
    return BookInfo();
  }
  if (!KeepDBOpen(path_to_file, q_sql_database_)) {
    return BookInfo();
  }

  QSqlQuery query;
  QString cmd;

  cmd = "SELECT language FROM manifest WHERE id = 1";
  query.prepare(cmd);
  if (!query.exec()) {
    qDebug() << cmd << query.lastError();
    return BookInfo();
  } else {
    query.next();
    info.language = StringToSupportLanguage(query.value(0).toString());
  }

  cmd = "SELECT COUNT(*) FROM vocabulary";
  query.prepare(cmd);
  if (!query.exec()) {
    qDebug() << cmd << query.lastError();
    return BookInfo();
  } else {
    query.next();
    info.word_num = query.value(0).toInt();
  }
  return info;
}

shared_ptr<Vocabulary> Database::LoadVocabulary(const QString &path_to_dir) {
  auto path_to_file = path_to_dir + "/" + DBFileName();
  if (!QFile(path_to_file).exists()) {
    return shared_ptr<Vocabulary>();
  }
  if (!KeepDBOpen(path_to_file, q_sql_database_)) {
    return shared_ptr<Vocabulary>();
  }
  shared_ptr<Vocabulary> vocabulary(new Vocabulary);
  QSqlQuery query;
  QString cmd;

  cmd =
      "SELECT"
      "  word,"
      "  meaning,"
      "  note,"
      "  hit,"
      "  hit_ts,"
      "  miss,"
      "  miss_ts,"
      "  require_spelling "
      "FROM vocabulary";
  query.prepare(cmd);
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
      vocabulary->PrepareWord(entry);
    }
  } else {
    qDebug() << cmd << query.lastError();
    return shared_ptr<Vocabulary>();
  }
  return vocabulary;
}

bool Database::KeepDBOpen(const QString& path_to_db, QSqlDatabase& db) {
  if (db.databaseName() != path_to_db) {
    db.setDatabaseName(path_to_db);
    if (!db.open()) {
      return false;
    }
  } else {
    if (!db.isOpen()) {
      if (!db.open()) {
        return false;
      }
    }
  }
  return true;
}

void Database::CloseDB(const QString &path) {
  auto path_to_db = path + "/" + DBFileName();
  if (q_sql_database_.databaseName() == path_to_db) {
    q_sql_database_.close();
  }
}

bool Database::WriteEntry(const WordEntry &entry, const QString &path_to_dir) {
  auto path_to_file = path_to_dir + "/" + DBFileName();
  if (!QFile(path_to_file).exists()) {
    return false;
  }
  if (!KeepDBOpen(path_to_file, q_sql_database_)) {
    return false;
  }

  QSqlQuery query;
  QString cmd;

  cmd =
      "SELECT COUNT(*) FROM vocabulary "
      "WHERE word = '" + entry.word + "'";
  query.prepare(cmd);
  if (!query.exec()) {
    qDebug() << cmd << query.lastError();
    return false;
  }
  query.next();
  if (query.value(0).toInt() > 0) {
    cmd =
        "DELETE FROM vocabulary "
        "WHERE word = '" + entry.word + "'";
    query.prepare(cmd);
    if (!query.exec()) {
      qDebug() << cmd << query.lastError();
      return false;
    }
  }

  cmd =
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
      ")";
  query.prepare(cmd);
  if (!query.exec()) {
    qDebug() << cmd << query.lastError();
    return false;
  }

  return true;
}

bool Database::DeleteEntry(const QString &word, const QString &path_to_dir) {
  auto path_to_file = path_to_dir + "/" + DBFileName();
  if (!QFile(path_to_file).exists()) {
    return false;
  }
  if (!KeepDBOpen(path_to_file, q_sql_database_)) {
    return false;
  }

  QSqlQuery query;
  QString cmd;

  cmd =
      "SELECT COUNT(*) FROM vocabulary "
      "WHERE word = '" + word + "'";
  query.prepare(cmd);
  if (!query.exec()) {
    qDebug() << cmd << query.lastError();
    return false;
  }
  query.next();
  if (query.value(0).toInt() > 0) {
    cmd =
        "DELETE FROM vocabulary "
        "WHERE word = '" + word + "'";
    query.prepare(cmd);
    if (!query.exec()) {
      qDebug() << cmd << query.lastError();
      return false;
    }
  }
  return true;
}

WordEntry Database::LookUp(const QString &word, const QString &path_to_dir) {
  auto path_to_file = path_to_dir + "/" + DBFileName();
  if (!QFile(path_to_file).exists()) {
    return WordEntry();
  }
  if (!KeepDBOpen(path_to_file, q_sql_database_)) {
    return WordEntry();
  }

  QSqlQuery query;
  QString cmd;

  cmd =
      "SELECT"
      "  word,"
      "  meaning,"
      "  note,"
      "  hit,"
      "  hit_ts,"
      "  miss,"
      "  miss_ts,"
      "  require_spelling "
      "FROM vocabulary "
      "WHERE word = '" + word + "'";
  query.prepare(cmd);
  if (query.exec()) {
    WordEntry entry;
    for (int row = 0; query.next(); ++row) {
      int i = 0;
      entry.word = query.value(i++).toString();
      entry.meaning = query.value(i++).toString();
      entry.note = query.value(i++).toString();
      entry.hit = query.value(i++).toInt();
      entry.hit_ts = query.value(i++).toString();
      entry.miss = query.value(i++).toInt();
      entry.miss_ts = query.value(i++).toString();
      entry.require_spelling = query.value(i++).toInt();
    }
    return entry;
  } else {
    qDebug() << cmd << query.lastError();
    return WordEntry();
  }
  return WordEntry();
}
