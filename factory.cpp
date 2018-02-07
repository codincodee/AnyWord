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

  main_window_word_ui_.reset(new MainWindowWordUI);
  main_window_word_ui_->SetQtLabel(qt_main_window_->WordLabel());
  main_window_word_ui_->SetDefault();

  main_window_meaning_ui_.reset(new MainWindowMeaningUI);
  main_window_meaning_ui_->SetQtLabel(qt_main_window_->MeaningLabel());
  main_window_meaning_ui_->SetDefault();
  return true;
}
