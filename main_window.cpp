#include "main_window.h"
#include "ui_main_window.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::Init() {
  ui->setupUi(this);

  // Word Label
  auto word_label = WordLabel();
  QFont font = word_label->font();
  font.setBold(true);
  font.setPointSize(30);
  word_label->setFont(font);
  word_label->setText("Welcome");

  // Meaning Label
  auto meaning_label = MeaningLabel();
  font = meaning_label->font();
  font.setBold(true);
  font.setPointSize(20);
  meaning_label->setFont(font);
  meaning_label->setText("y");
  meaning_label->setVisible(false);

  // "I know" Button
  auto i_know_push_button = IKnowPushButton();
  font = i_know_push_button->font();
  font.setBold(true);
  font.setPointSize(10);
  i_know_push_button->setFont(font);
  i_know_push_button->setFocus();

  // "I Don't Know" Button
  auto i_dont_know_push_button = IDontKnowPushButton();
  font = i_dont_know_push_button->font();
  font.setBold(true);
  font.setPointSize(10);
  i_dont_know_push_button->setFont(font);

  // Progress
  auto progress_bar = ProgressBar();
  progress_bar->setStyleSheet(
      "QProgressBar {"
          "border: 0px solid grey;"
          "border-radius: 0px;"
          "text-align: center;"
      "}"
      "QProgressBar::chunk {"
          "background-color: #05B8CC;"
          "width: 1px;"
      "}");
  progress_bar->setValue(0);

  // Playback
  auto play_back_push_button = PlaybackPushButton();
  play_back_push_button->setVisible(false);

  QAction* action_add_words = new QAction("Add Words", this);
  connect(action_add_words, &QAction::triggered, this, &MainWindow::OnActionAddWordsTriggered);
  ui->SettingsToolButton->addAction(action_add_words);

  add_words_main_window_ = new AddWordsMainWindow(this);
  return true;
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
  if (add_words_main_window_) {
    add_words_main_window_->show();
  }
}
