#include "add_words_main_window.h"
#include "ui_add_words_main_window.h"
#include <QDebug>
#include <QThread>

AddWordsMainWindow::AddWordsMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AddWordsMainWindow)
{
  ui->setupUi(this);
  this->setWindowModality(Qt::WindowModal);
  ui->DeletePushButton->setVisible(false);

  // All Widgets
  all_widgets_.push_back(ui->WordLineEdit);
  all_widgets_.push_back(ui->MeaningLineEdit);
  all_widgets_.push_back(ui->RecordRadioButton);
  all_widgets_.push_back(ui->PlayToolButton);
  all_widgets_.push_back(ui->NotePlainTextEdit);
  all_widgets_.push_back(ui->DeletePushButton);
  all_widgets_.push_back(ui->ClearPushButton);
  all_widgets_.push_back(ui->OkPushButton);
}

AddWordsMainWindow::~AddWordsMainWindow()
{
  delete ui;
}

void AddWordsMainWindow::DisableWidgets(
    std::vector<QWidget *> &widgets, const bool& disable) {
  for (auto& widget : widgets) {
    widget->setDisabled(disable);
  }
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
  WordEntry entry;
  emit WriteDatabase(entry);
}

void AddWordsMainWindow::on_WordLineEdit_editingFinished()
{
  if (ui->WordLineEdit->text().isEmpty()) {
    return;
  }
  ui->HintLabel->setText("Searching vocabulary...");
  DisableWidgets(all_widgets_, true);
  qApp->processEvents();
  WordEntry entry;
  entry.word = ui->WordLineEdit->text();
  emit SearchDatabase(entry);
  DisableWidgets(all_widgets_, false);
  ui->HintLabel->setText("Please continue.");
  qApp->processEvents();
  if (entry.Empty()) {
    return;
  }
  ui->WordLineEdit->setText(entry.word);
  ui->MeaningLineEdit->setText(entry.meaning);
  ui->NotePlainTextEdit->setPlainText(entry.note);
}
