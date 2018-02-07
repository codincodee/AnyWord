#include "main_window_word_ui.h"

MainWindowWordUI::MainWindowWordUI() : qt_label_(nullptr)
{

}

void MainWindowWordUI::SetQtLabel(QLabel *label) {
  qt_label_ = label;
}

bool MainWindowWordUI::SetDefault() {
  if (!qt_label_) {
    return false;
  }
  QFont font = qt_label_->font();
  font.setBold(true);
  font.setPointSize(30);
  qt_label_->setFont(font);
  return true;
}
