#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <memory>

class Database : public QObject
{
  Q_OBJECT
public:
  Database();
public slots:
  void OnWriteDataBase(std::shared_ptr<int> db);
};

#endif // DATABASE_H
