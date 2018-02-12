#include "select_book_main_window.h"
#include "ui_select_book_main_window.h"
#include <QDebug>
#include "ui_utils.h"
#include <QMessageBox>

SelectBookMainWindow::SelectBookMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SelectBookMainWindow)
{
  ui->setupUi(this);
  this->setWindowModality(Qt::WindowModal);
  auto all_supporting_languages = AllSupportingLanguagesString();
  ui->LanguageComboBox->addItems(all_supporting_languages);
}

SelectBookMainWindow::~SelectBookMainWindow()
{
  delete ui;
}

void SelectBookMainWindow::RegisterBookListCallback(
    std::function<std::vector<BookInfo> ()> func) {
  book_list_callback_ = func;
}

void SelectBookMainWindow::RegisterBookInfoCallback(
    std::function<BookInfo (const QString &)> func) {
  book_info_callback_ = func;
}

void SelectBookMainWindow::RegisterCreateBookCallback(
    std::function<bool (const BookInfo&)> func) {
  create_book_callback_ = func;
}

void SelectBookMainWindow::RegisterDeleteBookCallback(
    std::function<bool (const QString &)> func) {
  delete_book_callback_ = func;
}

void SelectBookMainWindow::showEvent(QShowEvent *event) {
  Q_UNUSED(event);
  RefreshBookList();
  QMainWindow::showEvent(event);
}

void SelectBookMainWindow::on_PickPushButton_clicked()
{
  this->hide();
  qApp->processEvents();
  emit SelectBook(ui->BookComboBox->currentText());
}

void SelectBookMainWindow::on_BookComboBox_currentTextChanged(const QString &arg1)
{
  ui->SummaryTextEdit->clear();
  Q_UNUSED(arg1);
  BookInfo book;
  if (book_info_callback_) {
    book = book_info_callback_(ui->BookComboBox->currentText());
  }
  if (!book.Empty()) {
    ui->SummaryTextEdit->setText("Language: " + SupportLanguageToString(book.language) + "\nTotal Words: " + QString::number(book.word_num));
  }
}

void SelectBookMainWindow::on_CreatePushButton_clicked()
{
  auto book_name = ui->CreateBookNameLineEdit->text();
  if (book_name.isEmpty()) {
    return;
  }

  if (book_info_callback_) {
    auto book = book_info_callback_(book_name);
    if (!book.Empty()) {
      ui::warn("Book already exists.", this);
      return;
    }
  } else {
    qDebug() << "Book Info callback not registered!";
    return;
  }

  BookInfo info;
  info.name = book_name;
  info.language = StringToSupportLanguage(ui->LanguageComboBox->currentText());

  if (create_book_callback_) {
    if (!create_book_callback_(info)) {
      ui::warn("Unable to create a book!", this);
    } else {
      ui::info("Book created!", this);
      ui->CreateBookNameLineEdit->clear();
      RefreshBookList();
    }
  } else {
    qDebug() << "Create Book callback not registered!";
  }
}

void SelectBookMainWindow::RefreshBookList() {
  ui->BookComboBox->clear();
  if (book_list_callback_) {
    auto list = book_list_callback_();
    for (auto book : list) {
      ui->BookComboBox->addItem(book.name);
    }
  }
}

void SelectBookMainWindow::on_DeletePushButton_clicked()
{
  auto book_name = ui->BookComboBox->currentText();
  if (book_name.isEmpty()) {
    return;
  }
  if (QMessageBox::question(
          this, "Confirm", "Are you sure to delete the book?",
          QMessageBox::Yes, QMessageBox::Cancel) != QMessageBox::Yes) {
    return;
  }

  if (delete_book_callback_) {
    if (delete_book_callback_(book_name)) {
      RefreshBookList();
    } else {
      ui::warn("Unable to delete the book!", this);
    }
  } else {
    qDebug() << "Delete Book callback not registered!";
  }
}
