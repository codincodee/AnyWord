#include "select_book_main_window.h"
#include "ui_select_book_main_window.h"
#include <QDebug>

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

void SelectBookMainWindow::showEvent(QShowEvent *event) {
  Q_UNUSED(event);
  ui->BookComboBox->clear();
  if (book_list_callback_) {
    auto list = book_list_callback_();
    for (auto book : list) {
      ui->BookComboBox->addItem(book.name);
    }
  }
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
  if (!book.Emtpy()) {
    ui->SummaryTextEdit->setText(book.summary);
  }
}
