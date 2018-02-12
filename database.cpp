#include "database.h"
#include <QDebug>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

Database::Database()
{

}

bool Database::Init() {
  return true;
}

bool Database::NewDB(const QString& path) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path + "/book.db");
  if (!db.open()) {
    return false;
  }
  QSqlQuery query;
  query.prepare(
      "CREATE TABLE entry ("
      "word VARCHAR(50) UNIQUE PRIMARY KEY, meaning VARCHAR(100), note VARCHAR(100))");
  if (!query.exec()) {
    qDebug() << query.lastError();
    db.close();
  } else {
    qDebug() << "Table created!";
  }

  query.prepare("INSERT INTO entry (word, meaning, note) VALUES('the word A', 'the meaning', 'the note')");
  if (!query.exec()) {
    qDebug() << query.lastError();
  } else {
    qDebug("Inserted");
  }

  query.prepare("INSERT INTO entry (word, meaning, note) VALUES('the word', 'the meaning', 'the note')");
  if (!query.exec()) {
    qDebug() << query.lastError();
  } else {
    qDebug("Inserted");
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

