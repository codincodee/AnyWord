#include "database.h"
#include <QDebug>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

Database::Database()
{

}

bool Database::Init() {
  return true;
}

bool Database::NewDB(const QString& path, const BookInfo& info) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path + "/book.db");
  if (!db.open()) {
    return false;
  }
  QSqlQuery query;
  query.prepare("CREATE TABLE info (id INTEGER UNIQUE PRIMARY KEY, language VARCHAR(50), version VARCHAR(10))");
  if (!query.exec()) {
    qDebug() << query.lastError();
    return false;
  }

  query.prepare("INSERT INTO info (id, language, version) VALUES(1, '" + SupportLanguageToString(info.language) + "', 'v1.0.0')");
  if (!query.exec()) {
    qDebug() << query.lastError();
    return false;
  }

  query.prepare(
      "CREATE TABLE entry ("
      "word VARCHAR(50) UNIQUE PRIMARY KEY, meaning VARCHAR(100), note VARCHAR(100))");
  if (!query.exec()) {
    qDebug() << query.lastError();
    return false;
  }

  query.prepare("INSERT INTO entry (word, meaning, note) VALUES('the word A', 'the meaning', 'the note')");
  if (!query.exec()) {
    qDebug() << query.lastError();
  }

  query.prepare("INSERT INTO entry (word, meaning, note) VALUES('the word', 'the meaning', 'the note')");
  if (!query.exec()) {
    qDebug() << query.lastError();
  }

  query.prepare("SELECT language FROM info WHERE id = 1");
  if (!query.exec()) {
    qDebug() << query.lastError();
    return false;
  } else {
    query.next();
    QWidget widget;
    QMessageBox::information(&widget, "test", query.value(0).toString());
  }

  query.prepare("SELECT COUNT(*) FROM entry");
  if (!query.exec()) {
    qDebug() << query.lastError();
  } else {
    query.next();
    qDebug() << "Num:" << query.value(0).toInt();
  }
  db.close();
  return true;
}

