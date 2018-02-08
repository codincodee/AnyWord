#include "main_window_ui_control.h"

MainWindowUIControl::MainWindowUIControl()
{

}

void MainWindowUIControl::SetWordQtLabel(QLabel* label) {
  qt_label_word_ = label;
}

void MainWindowUIControl::SetMeaningQtLabel(QLabel* label) {
  qt_label_meaning_ = label;
}

void MainWindowUIControl::SetIKnowQtPushButton(QPushButton* button) {
  qt_push_button_i_know_ = button;
}

void MainWindowUIControl::SetIDontKnowQtPushButton(QPushButton* button) {
  qt_push_button_i_dont_know_ = button;
}

void MainWindowUIControl::SetPlaybackQtToolButton(QToolButton *button) {
  qt_push_button_playback_ = button;
}

void MainWindowUIControl::SetProgressQtProgressBar(QProgressBar *progress) {
  qt_progress_bar_progress_ = progress;
}

int MainWindowUIControl::SetDefaultUI() {
  // Word Label
  if (!qt_label_word_) {
    return false;
  }
  QFont font = qt_label_word_->font();
  font.setBold(true);
  font.setPointSize(30);
  qt_label_word_->setFont(font);
  qt_label_word_->setText("X");
  qt_label_word_->setVisible(false);

  // Meaning Label
  if (!qt_label_meaning_) {
    return false;
  }
  font = qt_label_meaning_->font();
  font.setBold(true);
  font.setPointSize(20);
  qt_label_meaning_->setFont(font);
  qt_label_meaning_->setText("y");
  qt_label_meaning_->setVisible(false);

  // "I know" Button
  if (!qt_push_button_i_know_) {
    return false;
  }
  font = qt_push_button_i_know_->font();
  font.setBold(true);
  font.setPointSize(10);
  qt_push_button_i_know_->setFont(font);
  qt_push_button_i_know_->setFocus();

  // "I Don't Know" Button
  if (!qt_push_button_i_dont_know_) {
    return false;
  }
  font = qt_push_button_i_dont_know_->font();
  font.setBold(true);
  font.setPointSize(10);
  qt_push_button_i_dont_know_->setFont(font);

  // Progress
  if (!qt_progress_bar_progress_) {
    return false;
  }
  qt_progress_bar_progress_->setStyleSheet(
      "QProgressBar {"
          "border: 0px solid grey;"
          "border-radius: 0px;"
          "text-align: center;"
      "}"
      "QProgressBar::chunk {"
          "background-color: #05B8CC;"
          "width: 1px;"
      "}");
  qt_progress_bar_progress_->setValue(0);

  // Playback
  qt_push_button_playback_->setVisible(false);
  return true;

}
