#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <memory>
#include "word_entry.h"
#include "object_base.h"
#include "vocabulary.h"

class Database : public ObjectBase
{
  Q_OBJECT
public:
  Database();
  bool Init();
  static QString DBFileName();
  static bool NewDB(const QString& path, const BookInfo& info);
  static BookInfo ReadBookInfoFromDB(const QString& path);
  static std::shared_ptr<Vocabulary> LoadVocabulary(const QString& path);
  static bool WriteEntry(const WordEntry& entry, const QString& path);
};

#endif // DATABASE_H
