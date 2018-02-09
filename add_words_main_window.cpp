#include "add_words_main_window.h"
#include "ui_add_words_main_window.h"
#include <QDebug>

AddWordsMainWindow::AddWordsMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AddWordsMainWindow)
{
  ui->setupUi(this);
  this->setWindowModality(Qt::WindowModal);
  ui->DeletePushButton->setVisible(false);
}

AddWordsMainWindow::~AddWordsMainWindow()
{
  delete ui;
}

void AddWordsMainWindow::on_OkPushButton_clicked()
{
//  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//  db.setDatabaseName("vocabulary_test");
//  qDebug() << db.open();
////  QSqlQuery query("CREATE TABLE people (ids integer primary key, name, text)");
////  query.prepare("INSERT INTO people (name) VALUES (:name)");
////  query.bindValue(":name", "kevinz");
////  qDebug() << query.exec();
  auto i = std::shared_ptr<int>(new int(2));
  emit WriteDatabase(i);
}
