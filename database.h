#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <memory>
#include "word_entry.h"

class Database : public QObject
{
  Q_OBJECT
public:
  Database();
public slots:
  void OnWriteDatabase(std::shared_ptr<int> db);
  void OnSearchDatabase(WordEntry& entry);
};

#endif // DATABASE_H
