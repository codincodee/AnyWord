#include "minimized_main_window.h"
#include "ui_minimized_main_window.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QDebug>
#include <QMouseEvent>

MinimizedMainWindow::MinimizedMainWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MinimizedMainWindow)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  auto desktop = QApplication::desktop()->availableGeometry();
  auto window = this->rect();
  this->move(desktop.topLeft() - window.topLeft());

  widgets_.push_back(ui->MessageLabel);
  widgets_.push_back(ui->CheckPushButton);
  widgets_.push_back(ui->CrossPushButton);
  widgets_.push_back(ui->PassPushButton);
}

MinimizedMainWindow::~MinimizedMainWindow()
{
  delete ui;
}

void MinimizedMainWindow::OnSwitchWindow() {
  this->setVisible(!this->isVisible());
}

void MinimizedMainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    SetAllWidgetsVisible(!ui->MessageLabel->isVisible());
  }
}

void MinimizedMainWindow::SetAllWidgetsVisible(const bool &visible) {
  for (auto& widget : widgets_) {
    widget->setVisible(visible);
  }
}
