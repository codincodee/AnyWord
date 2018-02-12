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
  static bool NewDB(const QString& path);
};

#endif // DATABASE_H
