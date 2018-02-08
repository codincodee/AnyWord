#ifndef MAIN_WINDOW_UI_CONTROL_H
#define MAIN_WINDOW_UI_CONTROL_H

#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QToolButton>

class MainWindowUIControl
{
public:
  MainWindowUIControl();
  void SetWordQtLabel(QLabel* label);
  void SetMeaningQtLabel(QLabel* label);
  void SetIKnowQtPushButton(QPushButton* button);
  void SetIDontKnowQtPushButton(QPushButton* button);
  void SetProgressQtProgressBar(QProgressBar* progress);
  void SetPlaybackQtToolButton(QToolButton* button);
  int SetDefaultUI();
private:
  QLabel* qt_label_word_ = nullptr;
  QLabel* qt_label_meaning_ = nullptr;
  QPushButton* qt_push_button_i_know_ = nullptr;
  QPushButton* qt_push_button_i_dont_know_ = nullptr;
  QToolButton* qt_push_button_playback_ = nullptr;
  QProgressBar* qt_progress_bar_progress_ = nullptr;
};

#endif // MAIN_WINDOW_UI_CONTROL_H
