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
  bool Init();
public slots:
  void OnWriteDatabase(const WordEntry& entry);
  void OnSearchDatabase(WordEntry& entry);
};

#endif // DATABASE_H
