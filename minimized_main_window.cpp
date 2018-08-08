#include "minimized_main_window.h"
#include "ui_minimized_main_window.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QDebug>
#include <QMouseEvent>
#include <QShortcut>
#include <QRect>

MinimizedMainWindow::MinimizedMainWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MinimizedMainWindow)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  QRect desktop = QApplication::desktop()->availableGeometry();
  auto window = this->rect();
  this->move(desktop.topLeft() - window.topLeft());

  widgets_.push_back(ui->MessageLabel);
//  widgets_.push_back(ui->CheckPushButton);
//  widgets_.push_back(ui->CrossPushButton);
//  widgets_.push_back(ui->PassPushButton);

  ui->CheckPushButton->setVisible(false);
  ui->CrossPushButton->setVisible(false);
  ui->PassPushButton->setVisible(false);

  QShortcut* shortcut;
  shortcut = new QShortcut(QKeySequence("x"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(on_CrossPushButton_clicked()));
  shortcut = new QShortcut(QKeySequence("v"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(on_CheckPushButton_clicked()));
  shortcut = new QShortcut(QKeySequence("o"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(on_PassPushButton_clicked()));
  shortcut = new QShortcut(QKeySequence("p"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(on_PassPushButton_clicked()));
  shortcut = new QShortcut(QKeySequence("b"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(on_PassPushButton_clicked()));
  shortcut = new QShortcut(QKeySequence("z"), this);
  connect(
      shortcut, SIGNAL(activated()), this, SLOT(OnShowHideSwitch()));
}

MinimizedMainWindow::~MinimizedMainWindow()
{
  delete ui;
}

void MinimizedMainWindow::OnSwitchWindow() {
  this->setVisible(!this->isVisible());
}

void MinimizedMainWindow::OnDisplayWord(const WordEntry &word) {
  ui->MessageLabel->setStyleSheet(QStringLiteral("QLabel{color: black}"));
  ui->MessageLabel->setText(word.word);
}

void MinimizedMainWindow::OnDisplayWordMeaning(
    const WordEntry &word, const bool &know) {
  if (know) {
    ui->MessageLabel->setStyleSheet(QStringLiteral("QLabel{color: green}"));
  } else {
    ui->MessageLabel->setStyleSheet(QStringLiteral("QLabel{color: red}"));
  }
  ui->MessageLabel->setText(word.word + ": " + word.meaning);
}

void MinimizedMainWindow::OnShowHideSwitch() {
  SetAllWidgetsVisible(!ui->MessageLabel->isVisible());
}

void MinimizedMainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    OnShowHideSwitch();
  }
  return QWidget::mousePressEvent(event);
}

void MinimizedMainWindow::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    this->move(mapToParent(QCursor::pos() - this->pos()));
  }
}

void MinimizedMainWindow::SetAllWidgetsVisible(const bool &visible) {
  for (auto& widget : widgets_) {
    widget->setVisible(visible);
  }
}

void MinimizedMainWindow::on_PassPushButton_clicked()
{
  emit PassPushButtonClicked();
}

void MinimizedMainWindow::on_CheckPushButton_clicked()
{
  emit CheckPushButtonClicked();
}

void MinimizedMainWindow::on_CrossPushButton_clicked()
{
  emit CrossPushButtonClicked();
}
