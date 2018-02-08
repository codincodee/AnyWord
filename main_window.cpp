#include "main_window.h"
#include "ui_main_window.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QAction* action_add_words = new QAction("Add Words", this);
  connect(action_add_words, &QAction::triggered, this, &MainWindow::OnActionAddWordsTriggered);
  ui->SettingsToolButton->addAction(action_add_words);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::SetFactory(std::shared_ptr<Factory> factory) {
  factory_ = factory;
}

QLabel* MainWindow::WordLabel() {
  return ui->WordLabel;
}

QLabel* MainWindow::MeaningLabel() {
  return ui->MeaningLabel;
}

QPushButton* MainWindow::IKnowPushButton() {
  return ui->IKnowTheWordPushButton;
}

QPushButton* MainWindow::IDontKnowPushButton() {
  return ui->IDontKnowTheWordPushButton;
}

QToolButton* MainWindow::PlaybackPushButton() {
  return ui->PlaybackToolButton;
}

QProgressBar* MainWindow::ProgressBar() {
  return ui->ProgressBar;
}

void MainWindow::on_SettingsToolButton_clicked()
{
  ui->SettingsToolButton->showMenu();
}

void MainWindow::OnActionAddWordsTriggered(bool checked) {
  if (factory_) {
    factory_->GetAddWordsMainWindow()->show();
  }
}
