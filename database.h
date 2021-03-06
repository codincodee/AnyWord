#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <memory>
#include "word_entry.h"
#include "object_base.h"
#include "vocabulary.h"
#include <QSqlDatabase>

class Database : public ObjectBase
{
  Q_OBJECT
public:
  Database();
  static bool Init();
  static QString DBFileName();
  static bool NewDB(const QString& path, const BookInfo& info);
  static BookInfo ReadBookInfoFromDB(const QString& path_to_dir);
  static std::shared_ptr<Vocabulary> LoadVocabulary(const QString& path_to_dir);
  static bool ClearHistory(const QString& path_to_dir);
  static bool WriteEntry(const WordEntry& entry, const QString& path_to_dir);
  static bool DeleteEntry(const QString& word, const QString& path_to_dir);
  static WordEntry LookUp(const QString& word, const QString& path_to_dir);
  static void CloseDB(const QString& path);
private:
  static bool KeepDBOpen(const QString& path_to_db, QSqlDatabase& db);
  static bool FilterString(QString& str);
  static bool FilterEntry(WordEntry& entry);
  static std::shared_ptr<QSqlDatabase> q_sql_database_;
};

#endif // DATABASE_H
