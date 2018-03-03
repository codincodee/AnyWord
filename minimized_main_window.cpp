#include "minimized_main_window.h"
#include "ui_minimized_main_window.h"

MinimizedMainWindow::MinimizedMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MinimizedMainWindow)
{
  ui->setupUi(this);
}

MinimizedMainWindow::~MinimizedMainWindow()
{
  delete ui;
}
