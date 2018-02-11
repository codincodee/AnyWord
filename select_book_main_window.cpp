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

void SelectBookMainWindow::on_PickPushButton_clicked()
{
  emit SelectBook(ui->BookComboBox->currentText());
}
