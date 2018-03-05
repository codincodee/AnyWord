#include "minimized_main_window.h"
#include "ui_minimized_main_window.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QDebug>

MinimizedMainWindow::MinimizedMainWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MinimizedMainWindow)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  auto desktop = QApplication::desktop()->availableGeometry();
  auto window = this->rect();
  this->move(desktop.topLeft() - window.topLeft());
}

MinimizedMainWindow::~MinimizedMainWindow()
{
  delete ui;
}
