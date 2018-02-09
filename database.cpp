#include "database.h"
#include <QDebug>
#include <QThread>

Database::Database()
{

}

void Database::OnWriteDatabase(std::shared_ptr<int> db) {
  *db = 10;
}

void Database::OnSearchDatabase(WordEntry &entry) {
  QThread::sleep(2);
  entry.meaning = "adsfasf";
  entry.note = "1. asdfa\n2. asdfasdfasdf\n3. adsfasd";
}
