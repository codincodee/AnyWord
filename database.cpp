#include "database.h"
#include <QDebug>
#include <QThread>

Database::Database()
{

}

bool Database::Init() {

}

void Database::OnWriteDatabase(const WordEntry& entry) {
  qDebug() << "asdfsa";
}

void Database::OnSearchDatabase(WordEntry &entry) {
  QThread::sleep(2);
  entry.meaning = "adsfasf";
  entry.note = "1. asdfa\n2. asdfasdfasdf\n3. adsfasd";
}
