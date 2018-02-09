#include "select_book_main_window.h"
#include "ui_select_book_main_window.h"

SelectBookMainWindow::SelectBookMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SelectBookMainWindow)
{
  ui->setupUi(this);
}

SelectBookMainWindow::~SelectBookMainWindow()
{
  delete ui;
}
