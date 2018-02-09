#include "select_book_main_window.h"
#include "ui_select_book_main_window.h"

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

void SelectBookMainWindow::on_PickPushButton_clicked()
{
  BookInfo book;
  book.name = ui->BookComboBox->currentText();
  emit SelectResult(book);
}
