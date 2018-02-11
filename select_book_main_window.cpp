#include "select_book_main_window.h"
#include "ui_select_book_main_window.h"
#include <QDebug>
#include "ui_utils.h"

SelectBookMainWindow::SelectBookMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SelectBookMainWindow)
{
  ui->setupUi(this);
  this->setWindowModality(Qt::WindowModal);
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
    std::function<bool (const QString &)> func) {
  create_book_callback_ = func;
}
void SelectBookMainWindow::showEvent(QShowEvent *event) {
  Q_UNUSED(event);
  FreshBookList();
  QMainWindow::showEvent(event);
}

void SelectBookMainWindow::on_PickPushButton_clicked()
{
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
    ui->SummaryTextEdit->setText(book.summary);
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

  if (create_book_callback_) {
    if (!create_book_callback_(book_name)) {
      ui::warn("Unable to create a book!", this);
    } else {
      ui::info("Book created!", this);
      ui->CreateBookNameLineEdit->clear();
      FreshBookList();
    }
  } else {
    qDebug() << "Create Book callback not registered!";
  }
}

void SelectBookMainWindow::FreshBookList() {
  ui->BookComboBox->clear();
  if (book_list_callback_) {
    auto list = book_list_callback_();
    for (auto book : list) {
      ui->BookComboBox->addItem(book.name);
    }
  }
}
