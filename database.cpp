#include "database.h"
#include <QDebug>

Database::Database()
{

}

void Database::OnWriteDataBase(std::shared_ptr<int> db) {
  qDebug() << *db;
}
