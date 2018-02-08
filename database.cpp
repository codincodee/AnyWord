#include "database.h"
#include <QDebug>

Database::Database()
{

}

void Database::OnWriteDatabase(std::shared_ptr<int> db) {
  qDebug() << *db;
}
