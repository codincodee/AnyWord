#include "factory.h"
#include "main_window.h"

Factory::Factory()
{

}

void Factory::SetMainWindow(MainWindow *win) {
  qt_main_window_ = win;
}

bool Factory::Init() {
  if (!qt_main_window_) {
    return false;
  }

  // Main Window UI Control
  main_window_ui_control_.reset(new MainWindowUIControl);
  main_window_ui_control_->SetWordQtLabel(qt_main_window_->WordLabel());
  main_window_ui_control_->SetMeaningQtLabel(qt_main_window_->MeaningLabel());
  main_window_ui_control_->SetIKnowQtPushButton(
      qt_main_window_->IKnowPushButton());
  main_window_ui_control_->SetIDontKnowQtPushButton(
      qt_main_window_->IDontKnowPushButton());
  main_window_ui_control_->SetPlaybackQtToolButton(
      qt_main_window_->PlaybackPushButton());
  main_window_ui_control_->SetProgressQtProgressBar(
      qt_main_window_->ProgressBar());
  if (!main_window_ui_control_->SetDefaultUI()) {
    return false;
  }

  // Add Words Main Window
  add_words_main_window_ = new AddWordsMainWindow(qt_main_window_);
  return true;
}

AddWordsMainWindow* Factory::GetAddWordsMainWindow() {
  return add_words_main_window_;
}
