#include "add_words_main_window.h"
#include "ui_add_words_main_window.h"
#include <QDebug>
#include <QThread>
#include "ui_utils.h"
#include <QShortcut>

AddWordsMainWindow::AddWordsMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AddWordsMainWindow)
{
  ui->setupUi(this);
  this->setWindowModality(Qt::WindowModal);
  // ui->DeletePushButton->setVisible(false);

  // All Widgets
  all_widgets_.push_back(ui->WordLineEdit);
  all_widgets_.push_back(ui->MeaningLineEdit);
  all_widgets_.push_back(ui->RecordRadioButton);
  all_widgets_.push_back(ui->PlayToolButton);
  all_widgets_.push_back(ui->NotePlainTextEdit);
  all_widgets_.push_back(ui->DeletePushButton);
  all_widgets_.push_back(ui->ClearPushButton);
  all_widgets_.push_back(ui->OkPushButton);
  all_widgets_.push_back(ui->RequireSpellingCheckBox);

  QShortcut* shortcut;
  shortcut = new QShortcut(QKeySequence("r"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(OnRecordRadioButtonClicked()));
  shortcut = new QShortcut(QKeySequence("p"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(on_PlayToolButton_clicked()));
  shortcut = new QShortcut(QKeySequence("Ctrl+s"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(on_OkPushButton_clicked()));
  shortcut = new QShortcut(QKeySequence("m"), this);
  connect(
      shortcut, SIGNAL(activated()), ui->MeaningLineEdit, SLOT(setFocus()));
  shortcut = new QShortcut(QKeySequence("w"), this);
  connect(
      shortcut, SIGNAL(activated()), ui->WordLineEdit, SLOT(setFocus()));
}

AddWordsMainWindow::~AddWordsMainWindow()
{
  delete ui;
}

void AddWordsMainWindow::RegisterSearchBookCallback(
    std::function<WordEntry (const WordEntry &)> func) {
  search_book_callback_ = func;
}

void AddWordsMainWindow::RegisterWriteEntryCallback(
    std::function<bool (const WordEntry &)> func) {
  write_entry_callback_ = func;
}

void AddWordsMainWindow::RegisterRecordExistsCallback(
    std::function<bool ()> func) {
  record_exists_callback_ = func;
}

void AddWordsMainWindow::RegisterBookInfoCallback(
    std::function<BookInfo ()> func) {
  book_info_callback_ = func;
}

void AddWordsMainWindow::DisableWidgets(
    std::vector<QWidget *> &widgets, const bool& disable) {
  for (auto& widget : widgets) {
    widget->setDisabled(disable);
  }
}

void AddWordsMainWindow::on_OkPushButton_clicked()
{
  if (ui->WordLineEdit->text().isEmpty()) {
    ui->HintLabel->setText("Please type in a word.");
    return;
  }
  if (record_exists_callback_) {
    if (!record_exists_callback_()) {
      ui->HintLabel->setText("Please record audio.");
      return;
    }
  } else {
    ui::warn("No record_exists_callback_", this);
  }
  WordEntry entry;
  entry.word = ui->WordLineEdit->text();
  WordEntry search_result;
  if (search_book_callback_) {
    search_result = search_book_callback_(entry);
  }
  entry.meaning = ui->MeaningLineEdit->text();
  entry.note = ui->NotePlainTextEdit->toPlainText();
  entry.hit = search_result.hit;
  entry.miss = search_result.miss;
  entry.require_spelling = ui->RequireSpellingCheckBox->isChecked();
  if (write_entry_callback_) {
    write_entry_callback_(entry);
  }
  emit SaveRecord(entry.word);
  ui->WordLineEdit->clear();
  ui->MeaningLineEdit->clear();
  ui->NotePlainTextEdit->clear();
  ui->RequireSpellingCheckBox->setChecked(false);
  ui->HintLabel->setText("Input successfully!");
  ui->WordLineEdit->setFocus();
}

void AddWordsMainWindow::on_WordLineEdit_editingFinished()
{
  emit ClearRecord();
  auto word = ui->WordLineEdit->text();
  ui->WordLineEdit->setText(word.trimmed());
  ui->NotePlainTextEdit->clear();
  ui->MeaningLineEdit->clear();
  if (ui->WordLineEdit->text().isEmpty()) {
    return;
  }
  ui->HintLabel->setText("Searching vocabulary...");
  DisableWidgets(all_widgets_, true);
  qApp->processEvents();
  emit LoadRecord(word);
  WordEntry entry;
  entry.word = ui->WordLineEdit->text();
  WordEntry search_result;
  if (search_book_callback_) {
    search_result = search_book_callback_(entry);
  }
  DisableWidgets(all_widgets_, false);
  ui->HintLabel->setText("Please continue.");
  qApp->processEvents();
  if (search_result.Empty()) {
    return;
  }
  ui->WordLineEdit->setText(search_result.word);
  ui->MeaningLineEdit->setText(search_result.meaning);
  ui->NotePlainTextEdit->setPlainText(search_result.note);
  ui->RequireSpellingCheckBox->setChecked(search_result.require_spelling);
}

void AddWordsMainWindow::on_RecordRadioButton_clicked(bool checked)
{
  if (checked) {
    emit StartRecord();
  } else {
    emit StopRecord();
  }
}

void AddWordsMainWindow::OnRecordRadioButtonClicked() {
  on_RecordRadioButton_clicked(!ui->RecordRadioButton->isChecked());
  ui->RecordRadioButton->setChecked(!ui->RecordRadioButton->isChecked());
}

void AddWordsMainWindow::on_PlayToolButton_clicked()
{
  ui->RecordRadioButton->setChecked(false);
  emit PlayRecord();
}

void AddWordsMainWindow::on_MeaningLineEdit_editingFinished()
{
  this->setFocus();
}

void AddWordsMainWindow::on_DeletePushButton_clicked()
{
  auto word = ui->WordLineEdit->text();
  if (word.isEmpty()) {
    return;
  }
  emit ClearRecord();
  emit DeleteRecord(word);
  emit DeleteEntry(word);
  ui->WordLineEdit->clear();
  ui->MeaningLineEdit->clear();
  ui->NotePlainTextEdit->clear();
  ui->RequireSpellingCheckBox->setChecked(false);
  ui->HintLabel->setText("Entry deleted!");
}

void AddWordsMainWindow::OnLoadEntry(const QString &word) {
  ui->WordLineEdit->setText(word);
  qApp->processEvents();
  on_WordLineEdit_editingFinished();
}

void AddWordsMainWindow::OnShow() {
  emit CloseBook();
  if (book_info_callback_) {
    BookInfo info = book_info_callback_();
    ui->BookNameLabel->setText(info.name);
  }
  this->show();
}

void AddWordsMainWindow::hideEvent(QHideEvent *event) {
  if (book_info_callback_) {
    BookInfo info = book_info_callback_();
    if (!info.Empty()) {
      emit SelectBook(info.name);
    }
  }
  return QMainWindow::hideEvent(event);
}
